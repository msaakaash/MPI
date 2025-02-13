# MPI Codes Repository

This repository contains implementations of various parallel computing algorithms using **Message Passing Interface (MPI)**. These programs are designed to leverage distributed computing for efficient execution on multi-node systems.

## Prerequisites

Before running the MPI programs, ensure you have the following installed:

- **MPI Library** (e.g., OpenMPI or MPICH)
- **GCC or another C/C++ compiler** (if using C/C++)
- **Python (if using mpi4py for Python MPI programs)**

## Getting Started

### Clone the Repository

```sh
git clone https://github.com/your-username/your-mpi-repo.git
cd your-mpi-repo
```

### Compile the MPI Programs (C/C++)

```sh
mpicc program.c -o program
```

### Run the MPI Programs

```sh
mpirun -np <num_processes> ./program
```

For Python MPI programs:

```sh
mpirun -np <num_processes> python program.py
```


## Contributing

Feel free to contribute by adding new MPI implementations, optimizing existing ones, or improving documentation. Follow these steps:

1. Fork the repository
2. Create a new branch
3. Commit your changes
4. Push the branch and create a Pull Request

## License

This project is licensed under the MIT License.

## Contact

For any queries or discussions, reach out via GitHub Issues or email at `msaakaash@hotmail.com`.

