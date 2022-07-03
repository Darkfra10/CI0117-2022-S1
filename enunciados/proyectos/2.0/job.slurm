#!/bin/bash
#SBATCH --job-name=test_name
#SBATCH --output=result.txt
#SBATCH --partition=nu-wide
#SBATCH --ntasks=2
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:05:00
#SBATCH --mail-user=my_user@ucr.ac.cr
#SBATCH --mail-type=ALL

module load gcc /7.2.0
module load mpich /3.2.1-gcc-7.2.0

mpiexec -np 2 ../bin/my_executable
