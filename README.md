# Boilerplate generator (kotlin version)

## Installation
```shell
git clone https://github.com/Neutron17/cgener.git --recursive
cd cgener
make
```
Now the executable is in ```build/```

## Usage
- ```-t/--type:```

    boilerplate type: for example 'c' generates a c boilerplate project

    boilerplate templates are stored in the ```templates/``` directory

General syntax:
```shell
./build/cgener -t <project type> -o <output> -u <username>
```
Example:
```shell
./build/cgener -t c -o foo -u neutron17
```

## Contribution
All contribution is welcome

There is a ```TODO.md``` file, containing the todos
## License
this project is licensed under the ```GPL 3.0 License```, use it as such