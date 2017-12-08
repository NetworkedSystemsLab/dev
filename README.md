# root
Main depo for NSL Self Driving Car, AutoKnight
Steps to update github from the terminal:

1) Make your changes in the ~/root/dev directory

2) When ready to save to github, type:

cd ~/root

3) Check what needs to be done to commit your changes:

./statusgit

If there are files that are missing (i.e. you need to add new or modified files),
go to step 4). If there are files that need to be removed from git, go to step 5). if there is nothing to be done, there are no changes

4) Add new or modified files to git:

./addgit [directory_name] # to add all files from a directory

or

./addgit [directory_name]/[file_name] # to add a specific file

5) Remove a file from git:

./recrmgit [directory_name]/* # to recursively remove all files from a directory

or

./rmgit [directory_name]/[file_name] # to remove a specific file

6) Apply your changes

./gitcommit

7) Upload the changes to github:

./pushgit

8) if your system is out of sync with git, or to return to the current git:

./pullgit
