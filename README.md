# root
Main depo for NSL Self Driving Car, AutoKnight
To update the github from the working directory on the jetson, open a terminal:

Recursively move all files from the working directory to the github directory

cp -rp ~/dev ~/root

Check the status of the github changes

git status

Remove files from the github directory

git rm (removed file)

git rm -r /directory/subdirectory/*

git add (added file)

git add /directory

once you’re done, do git status again to make sure all the messages are green (or your branch is up-to-date with ‘origin/master’.

git commit 

git push
