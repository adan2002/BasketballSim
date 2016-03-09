## Webscraper for tables in html
## Use to read in NBA rosters from ESPN


setwd("C:/Users/Adan/Desktop/BasketballSim")

require(rvest)
require(dplyr)



################################################
############ Import NBA Rosters ###############
###############################################

# loop thru every nba team

NBA_teams <- c('ATL', 'BOS', 'BKN', 'CHA', 'CHI', 'CLE', 
               'DAL', 'DEN', 'DET', 'GSW', 'HOU', 'IND', 
               'LAC', 'LAL', 'MEM', 'MIA', 'MIL', 'MIN', 
               'NO', 'NYK', 'OKC', 'ORL', 'PHI', 'PHO', 
               'POR', 'SAC', 'SAS', 'TOR', 'UTH', 'WAS')

NBA_players <- NULL

for (name in NBA_teams){
  url <- paste0("http://espn.go.com/nba/team/roster/_/name/", name)
  table <- url %>%
    html() %>%
    html_table()
  
  roster <- table[[1]]
  colnames(roster) <- roster[2,] # assing header
  roster <- roster[-c(1,2),] # drop first two rows
  roster$Team <- name
    
  NBA_players <- rbind(NBA_players, roster) # merge tables
}

# reset dataframe row index
rownames(NBA_players) <- seq(length=nrow(NBA_players))


# dictionary mapping team abbv to city
# for some reason BOS & BKN, NO an NYK had to be swapped

cities <- list(ATL = "Atlanta", BOS = 'Brooklyn', BKN = "Boston",
                  CHA = "Charlotte", CHI = "Chicago", CLE = "Cleveland",
                  DAL = "Dallas", DEN = "Denver", DET = "Detroit", 
                  GSW  = "Golden State", HOU = "Houston", IND = "Indiana",
                  LAC = "LA Clippers", LAL = "LA Lakers", MEM = "Memphis",     
                  MIA = "Miami", MIL = "Milwaukee", MIN = "Minnesota",
                  NYK = "New Orleans", NO = "New York", OKC = "Oklahoma City", 
                  ORL = "Orlando", PHI = "Philadelphia", PHO = "Phoenix", 
                  POR = "Portland", SAC ="Sacramento", SAS = "San Antonio",
                  TOR = "Toronto", UTH = "Utah", WAS = "Washington")  

# import data
ratings <- tbl_df(read.csv(file = 'NBA 2K16 Ratings.csv', header = T))
roster <- tbl_df(read.csv(file = 'NBAplayers.csv', header = T)) %>%
  mutate(City = cities[Team])
roster$City <- sapply(roster$City, as.factor) # convert char to factor
ranks <- tbl_df(read.csv(file = 'RosterRanks.csv', header = T))

newRoster <- na.omit(left_join(roster, ranks, by = c("Fint", "LastName", "City")))


finalRoster <- na.omit(left_join(newRoster, ratings, by = c("FirstName", "LastName")))
finalRoster <- select(finalRoster, -c(FirstName, LastName, HT, Position.x, Fint, COLLEGE,
                                      X2015.2016.SALARY, WT, NO., City)) 
names(finalRoster) <- tolower(names(finalRoster)) # make headers lowercase
colnames(finalRoster)[4] <- "position"

# get team counts
t <- finalRoster %>% 
  group_by(team) %>%
  summarise( cnt = n())



write.csv(t, file = 'team_counts.csv', row.names = FALSE)
write.csv(finalRoster, file = 'NBA_roster_ratings.csv', row.names = FALSE)


########################################################
######### 2014-2015 NBA Schedule and Results ###########
########################################################


url <- "http://www.basketball-reference.com/leagues/NBA_2015_games.html?lid=header_seasons"
table <- url %>%
html() %>%
html_table()

reg_season <-  table[[1]]
reg_season <- tbl_df(reg_season[,c(1,4,5,6,7)])
names(reg_season) <-  c("Date", "Away", "Pts_A", "Home", "Pts_H")
 
# add a score differential column
reg_season <- mutate(reg_season, sd = Pts_H - Pts_A)
#write.csv(reg_season, file = '2014-2015_Schedule_Results.csv')

# create dictionary to link team abbrv with team name

NBA_teams <- list(ATL = "Atlanta Hawks", BOS = 'Boston Celtics', BKN = "Brooklyn Nets",
                  CHA = "Charlotte Hornets", CHI = "Chicago Bulls", CLE = "Cleveland Cavaliers",
                  DAL = "Dallas Mavericks", DEN = "Denver Nuggets", DET = "Detroit Pistons", 
                  GSW  = "Golden State Warriors", HOU = "Houston Rockets", IND = "Indiana Pacers",
                  LAC = "Los Angeles Clippers", LAL = "Los Angeles Lakers", MEM = "Memphis Grizzlies",     
                  MIA = "Miami Heat", MIL = "Milwaukee Bucks", MIN = "Minnesota Timberwolves",
                  NYK = "New York Knicks", NO = "New Orleans Pelicans", OKC = "Oklahoma City Thunder", 
                  ORL = "Orlando Magic", PHI = "Philadelphia 76ers", PHO = "Phoenix Suns", 
                  POR = "Portland Trail Blazers", SAC ="Sacramento Kings", SAS = "San Antonio Spurs",
                  TOR = "Toronto Raptors", UTH = "Utah Jazz", WAS = "Washington Wizards")  
              

Team_names <- c('ATL', 'BOS', 'BKN', 'CHA', 'CHI', 'CLE', 
               'DAL', 'DEN', 'DET', 'GSW', 'HOU', 'IND', 
               'LAC', 'LAL', 'MEM', 'MIA', 'MIL', 'MIN', 
               'NO', 'NYK', 'OKC', 'ORL', 'PHI', 'PHO', 
               'POR', 'SAC', 'SAS', 'TOR', 'UTH', 'WAS')

# intialize probability matrix 

probMat <- data.frame(matrix(vector(), 30, 30,
            dimnames=list(Team_names, Team_names)),
            stringsAsFactors=F)


# iterate over each team and filter reg_season table
# to calculate the probability the home team wins a game

for (team in Team_names){
  df <- filter(reg_season, Home == NBA_teams[team]) # filter for home team
  
  for (away_team in Team_names){ # filter for home vs away
    if (away_team == team){ # trivial case of comparing own team to itself
          # also the main diagonal of probability matrix
      #print (away_team == team)
      probMat[team, team] <- 0 # set equalt zero
    }
    else{ # otherwise
      d <- df %>% 
        filter(Away == NBA_teams[away_team]) %>% # isolate instance of team A vs team B
        mutate(W = Pts_H > Pts_A) # dummy variable for home wins
      dw <- summarise(d, wins = sum(W))
      sd_avg <- mean(d$sd)
      if (sd_avg <= 0){ # negative score differential
        probMat[team, away_team] <- 0.5 + sd_avg/100
      }
      else { # positive scoring margin
        probMat[team, away_team] <- (sd_avg/100)^2 + dw$wins/length(d$W)*0.5
        
      }
    }
  }
}


probMat

write.table(probMat,file="probs.txt", sep = ',', row.names =F, col.names = F)



#############################################
######### 2015-2016 NBA Schedule  ###########
#############################################

# source: basketball reference.com

url <- "http://www.basketball-reference.com/leagues/NBA_2016_games.html?lid=header_seasons"
table <- url %>%
  html() %>%
  html_table()


# truncate html table for desired columns
season <-  table[[1]]
season <- tbl_df(season[,c(1,4,6)])
names(season) <-  c("Away", "Home")

write.table(season,file="2016schedule.txt", sep = ',', row.names =F)

# read table back in
s <- tbl_df(read.csv(file = "2016schedule.csv", header = T))

for (i in 1:length(s$Away.City)){
  # match up Away team
  j = 1 # initialize counter
  
  tname = paste(s$Away.City[i], s$Away.Team[i]) # team name
  while (tname != NBA_teams[j]){
    j = j + 1  
    print(tname)
  }
   
  s$Away[i] = Team_names[j] # store team
  j = 1 # reset counter
  
  # match up Home team
  tname = paste(s$Home.City[i], s$Home.Team[i]) # team name
  while (tname != NBA_teams[j]){
    j = j + 1   
    print (tname)
  }
  
  s$Home[i] = Team_names[j] # store team
}



write.csv(s[,5:6],file="2016schedule.csv",  row.names =F)
