# Developing a Starlab Plugin #

There are two types of plugins you can easily write:
  * **Filter** plugin
  * **Mode** plugin

Simply copy any of the provided example plugins and rename them as your own.

## Filter ##
A filter plugin is a one way process on a selected model. You provide any number of parameters and then apply your algorithm. Example **'surfacemesh\_filter\_normalize'**.

The two functions to modify are:
```
    void initParameters( RichParameterSet* pars );
    void applyFilter( RichParameterSet* pars );
```

Where you can easily add parameters such as:
```
pars->addParam(new RichFloat("angle", 90.0f, "Maximum angle"));
pars->addParam(new RichBool("visualize", true, "Visualize result"));
```

And use them in your **applyFilter** method:
```
bool isVisualize = pars->getBool("visualize")
```

## Mode ##
A mode plugin gives you full control over the starlab interface. It is useful for interactive or more complex model processing. A tool button with an icon is added to the tool bar for each loaded mode plugin. Example **'surfacemesh\_mode\_arapdeform'** ([in action](http://www.youtube.com/watch?v=95KVrSfc1r8)).

Several functions to look into are:
```
void create();
void decorate();
bool keyPressEvent(QKeyEvent *);
```

The **create** function is called once the mode is selected. The **decorate** functions allows you to make OpenGL calls on the current scene. The **keyPressEvent** and other Qt keyboard and mouse widget events can be overloaded to include your own desired behavior.