# root
Main depo for NSL Self Driving Car, AutoKnight (rebranded as SCAVE)
SCAVE: Small-scale Cooperative Autonomous VEhicle

Steps to update github from the terminal:

1) Make your changes in this directory

2) Check what needs to be done to commit your changes:

	git status

If there are files that are missing (i.e. you need to add new or modified files),
go to step 3). If there are files that need to be removed from git, go to step 4). if there is nothing to be done, there are no changes

3) Add new or modified files to git:

	git add [directory_name] # to add all files from a directory

or

	git add [directory_name]/[file_name] # to add a specific file

5) Remove a file from git:

	git rm [directory_name] -r # to recursively remove all files from a directory

or

	git rm [directory_name]/[file_name] # to remove a specific file

6) Apply your changes

	git commit

7) Upload the changes to github:

	git push

8) if your system is out of sync with git, or to return to the current git:

	git pull
