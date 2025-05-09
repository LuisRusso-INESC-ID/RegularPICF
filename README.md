# RegularPICF 0.2.0-alpha

An implementation of Regular Periodic Infinite Continued Fractions. A
description of this implementation will be given in the paper. The
goal of this implemenation is provide a way to obtain Regular Periodic
Infinite Continued Fractions that represent a root of the input
polynomial of degree two.

## Table of contents

- [Getting Started]
   - [Prerequisites]
   - [Installing]
   - [Running]
- [Contributing]
- [Versioning]
- [Authors]
- [License]
- [Acknowledgments]

## Getting Started

To get a copy of this software download or clone the GitHub repository.

Download:

```
wget https://github.com/LuisRusso-INESC-ID/RegularPICF/archive/main.zip
```

Clone:

```
git clone https://github.com/LuisRusso-INESC-ID/RegularPICF.git
```

### Prerequisites

This package was tested with [Arch Linux], it will most likely work with
other Linux distributions and UNIX variants. The experimental evaluation
was performed on a [Debian] server. Some version of the following
components must exist in the system.

For the shell:

* C compiler, [gcc]
* [GNU Make]
* glibc
* The GNU Multiple Precision Arithmetic Library [GMP]

For the running tests:

* [sed]
* [gnuplot]
* /usr/bin/time

### Installing

Execute `make` to obtain the binaries `shell` and  `tester`.

```
make
```

Make sure to clean up before re-compiling, so:

```
make clean
make
```

### Running

To run commands simply call the `shell` binary. Then issue a command
followe by the necessary arguments. The commands `F` and `D` use
Floyd's algorithm. The commands `G` and `H` uses Galois's
criteria. The commands `F` and `G` receive as arguments a
polynomial. The commands `D` and `H` use the value of D instead of C
in the input. Here are some input output examples:

```
F 1 0 -61
7 ( 1 4 3 1 2 2 1 3 4 1 14 )
```

```
G 1 0 -61
7 ( 1 4 3 1 2 2 1 3 4 1 14 )
```

```
D 1 0 61
7 ( 1 4 3 1 2 2 1 3 4 1 14 )
```

```
H 1 0 61
7 ( 1 4 3 1 2 2 1 3 4 1 14 )
```

To build polynomial use the command `B`. The first argument indicates
the size of the cycle, i.e., n. Then next n numbers describe the
cycle. The next number indicates the size of the initial part, i.e.,
m. The next m numbers describe that part. Here is an example.

```
B 11 1 4 3 1 2 2 1 3 4 1 14 4 7 6 5 4
58596 x^2 -245725 * 2x +1030459
```

The command `P` is used to solve Pell's equation. The only argument is
the value of D. The following is an input output example.

```
P 61
1766319049^2 - 61 * 226153980^2 = 1
```

There is a script to run the tests in the paper and generate the
plots. Just run:

```
bash runTests.sh
```

This is script depends on the `tester` and `shell` binaries.

## Contributing

If you found this project useful please share it, also you can create an
[issue] with comments and suggestions.

## Versioning

We use [SemVer] for versioning. For the versions available, see the [tags]
on this repository.

## Authors

* **Luís M. S. Russo** - *Initial work* - [LuisRusso]

See also the list of [contributors] who participated in this project.

## License

This project is licensed under the MIT License - see
the [LICENSE file] for details

## Acknowledgments

* This software was produced for research that was funded in by national funds
through Fundação para a Ciência e Tecnologia ([FCT]) with reference
[DOI] 10.54499/UIDB/50021/2020.

* Thanks to [PurpleBooth] for the [README-Template].

[Getting Started]: #getting-started
[Prerequisites]: #prerequisites
[Installing]: #installing
[Running]: #running
[Contributing]: #contributing
[Versioning]: #versioning
[Authors]: #authors
[License]: #license
[Acknowledgments]: #acknowledgments

[gcc]: https://gcc.gnu.org/
[GNU Make]: https://www.gnu.org/software/make/
[GMP]: https://gmplib.org/
[sed]: https://www.gnu.org/software/sed/
[gnuplot]: http://www.gnuplot.info/

[issue]: ../../issues
[luis.russo@tecnico.ulisboa.pt]: mailto:luis.russo@tecnico.ulisboa.pt
[SemVer]: http://semver.org/
[tags]: ../../tags
[LuisRusso]: https://github.com/LuisRusso-INESC-ID
[contributors]: ../../contributors
[LICENSE file]: ./LICENSE
[FCT]: https://www.fct.pt/
[DOI]: https://doi.org/10.54499/UIDB/50021/2020
[PurpleBooth]: https://gist.github.com/PurpleBooth
[README-Template]: https://gist.github.com/PurpleBooth/109311bb0361f32d87a2

