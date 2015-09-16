# Git Primer
If you want to use the command line the majority of commands you'll need are listed here.

## Clone the repository
``git clone https://github.com/boristsr/redsquare.git``
## Update your local copy with changes others have submitted
`git pull`
## To see locally changed, added or deleted files
`git status`

## Committing changes
When you want to commit changes you need to stage files for committing, run git status to check what files are changed. Then to add the files you want type
`git add <files>`
Wild characters work here
`git add *.cpp *.h`
### Committing
Since git is a distributed VCS, you need to commit your changes to your repository, then push it to the main repository.
`git commit -m "Put a comment here about what you've changed"`

`git push origin master`

