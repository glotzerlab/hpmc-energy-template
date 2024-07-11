# HOOMD-blue component template for HPMC interaction energies

`hpmc-energy-template` provides a framework to develop components that extend
[**HOOMD-blue**](https://glotzerlab.engin.umich.edu/hoomd-blue/) with new pairwise and
external potentials for HPMC. It includes template C++ and Python modules, an example
unit test, CMake scripts to build the component, and GitHub Actions workflows.

## Building the component

To build this component:

1. Build and install **HOOMD-blue** from source.
2. Obtain the component's source.
    ```
    $ git clone https://github.com/glotzerlab/hoomd-component-template
    ```
3. Configure.
    ```
    $ cmake -B build/hoomd-component-template -S hoomd-component-template
    ```
4. Build the component.
    ```
    $ cmake --build build/hoomd-component-template
    ```
5. Install the component.
    ```
    $ cmake --install build/hoomd-component-template
    ```

Once installed, the template is available for import via:
```
import hoomd.hpmc_energy
```

## Creating a new component

To create a new component:

1. Fork [hpmc-energy-template](https://github.com/glotzerlab/hpmc-energy-template/).
2. Address all **TODO** comments (including those in `.github/`)
3. Add C++ and Python files to `src/`.
4. Add unit tests in `src/pytest`.
5. Format and check code style with [pre-commit](https://pre-commit.com/).

## Using the provided GitHub Actions configuration

When you push your changes to GitHub, the [unit test workflow](.github/workflows/unit-test.yaml)
compile your code on the CPU (with and without MPI) and on the GPU (with and without MPI). The
workflow also executes the unit tests on the CPU. You should run GPU unit tests locally, as GitHub
does not provide free GPU runners for GitHub Actions.

When you push a new tag, the [release workflow](.github/workflows/release.yaml) will create a
new GitHub release with automatically generated release notes.

## Maintaining your component

The HOOMD-blue developers will periodically update
[hpmc-energy-template](https://github.com/glotzerlab/hpmc-energy-template/), including
updates to the GitHub Actions workflow, pre-commit configuration, and CMake scripts. Merge these
changes into your fork to support the latest version of HOOMD-blue.

## Documenting and releasing your component

TODO: Document your component in `README.md` (this file) and remove documentation relevant to the
template.

When appropriate:

* Add [Sphinx](https://www.sphinx-doc.org) documentation and publish it on
[readthedocs](https://www.readthedocs.org).
* Add a [conda-forge](https://conda-forge.org/) package.
* Announce your component on the [HOOMD-blue discussion board](https://github.com/glotzerlab/hoomd-blue/discussions).
