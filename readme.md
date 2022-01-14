[![Documentation Status](https://readthedocs.org/projects/vdune/badge/?version=latest)](https://vdune.readthedocs.io/en/latest/?badge=latest)
# vDUNE

## Setup vDUNE

### Cloning
The following is the command to clone the repository.  Submodules should be initialized when this project is cloned:
> ```bash
> git clone https://github.com/demuth/vDUNE.git --recurse-submodules
> ```

### Subversion
We recommend Subversion for this project because it allows commits with a greater file size than git.

#### Install Subversion:
> Subversion can be installed via a package management tool like macports or homebrew.  
> ##### MacPorts:
> ```bash
> sudo port install subversion
> ```
> ##### Homebrew:
> ```bash
> brew install subversion
>```

#### Clone using Subversion:
> Enter the following command into a terminal or command prompt to checkout the repository.
> #### Subversion client
> ```bash
> svn checkout https://github.com/lmsorenson/vDUNE
> ```
>
> ##### git svn (Windows compatible):
> ```bash
> git svn clone -s https://github.com/lmsorenson/vDUNE
>```
