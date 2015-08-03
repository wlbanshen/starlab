# How to change the remote head #
the remote head is the branch that gets checked out by default:
```
git remote set-head origin REMOTE_BRANCH_NAME 
```

In our case the starlab\_full branch is our default checkout so:

```
git remote set-head origin starlab_full 
```

# How to completely discard last commit #
This is a **potentially dangerous** command, since it throws away all your uncommitted changes. For safety, you should always check that the output of git status is clean (i.e. empty) before using it.
```
git reset --hard HEAD^
```