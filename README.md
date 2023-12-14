# Procedural Modeling
Master thesis based on the paper Example-Based Procedural Modeling Using Graph Grammars by Paul Merrell [[link](https://paulmerrell.org/grammar/)]

## Setup

From now on, we use the following variables in commands:
- `$REPO_DIR`: the directory where you will clone your repository;
- `$BUILD_DIR`: the directory where you will build the project.

The project can be build as follows:

```
$ mkdir $BUILD_DIR
$ cd $BUILD_DIR
$ cmake $REPO_DIR
$ cmake --build .
```
Only the last step needs to be repeated when rebuilding the project.
Running the project can be done be running the executable `ProceduralModeling`.
