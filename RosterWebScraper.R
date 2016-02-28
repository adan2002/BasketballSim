## Webscraper for tables in html
## Use to read in NBA rosters from ESPN


setwd("C:/Users/Adan/Desktop/BasketballSim")

require(rvest)
require(dplyr)


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

# player rating
ratings <- tbl_df(read.csv(file = 'NBA 2K16 Ratings.csv', header = T))
roster <- tbl_df(read.csv(file = 'NBAplayers.csv', header = T))

finalroster <- na.omit(left_join(ratings, roster, by = c("FirstName", "LastName")))
finalroster <- select(finalroster, -c(HT, X, COLLEGE, X2015.2016.SALARY, WT, NO.)) 
names(finalroster) <- tolower(names(finalroster)) # make headers lowercase

# get team counts
t <- finalroster %>% 
  group_by(team) %>%
  summarise( cnt = n())



write.csv(t, file = 'team_counts.csv')
write.csv(finalroster, file = 'NBA_roster_ratings.csv')
