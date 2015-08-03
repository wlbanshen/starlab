# Accessing Qt variables #

```
  $$VAR returns local var 
  $${VAR} returns local var without spaces 
  $$[VAR] for ones set by qmake -set 
  $$(VAR) retrieves ENVIRONMENT variable 
```


# Differences from "load(**.prf)", "CONFIG+=" and "Include" #**

load(string) — Sort of a cross between include() and CONFIG += feature. load(foo) will look for a file called "foo.prf" in the standard feature path, and execute its contents immediately. Features that are contained within CONFIG are executed last, after the .pro file has finished processing. Like include(), it will return true if the file was found.

NOTE: load(..) was deprecated in Qt>4.8.4/5

# External Material #
http://doc.qt.nokia.com/stable/qmake-advanced-usage.html