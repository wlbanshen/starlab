# OSX #



# Typical windows errors #

### LNK2001: missing "export" directives ###
```
XXXXXX.obj : error LNK2001: unresolved external symbol "public: virtual struct QMetaObject 
const * __thiscall ModePlugin::metaObject(void)const " (metaObject@ModePlugin@@UBEPBUQMetaObject@@XZ)
```

This was caused by a missing export (STARLIB\_EXPORT) in `ModePlugin.h`
```
class STARLIB_EXPORT ModePlugin : public StarlabPlugin {
    Q_OBJECT
    ...
}
```