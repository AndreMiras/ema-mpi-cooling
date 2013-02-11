exec_cmd()
{
    echo "Running: $1"
    # TODO: is that the right way to do it?
    $1
    if [ $? != 0 ]
    then
        echo "Error while running: $1"
        post_install_cleaning
        exit 1
    fi
}

exec_cmd "mkdir -p dist/MPIcpp/GNU-Linux-x86/"
exec_cmd "mpic++ -g utils.cpp master.cpp -o dist/MPIcpp/GNU-Linux-x86/master"
exec_cmd "mpic++ -g utils.cpp calculator_slave.cpp -o dist/MPIcpp/GNU-Linux-x86/calculator_slave"

echo "run with:"
echo "mpirun -np 1 dist/MPIcpp/GNU-Linux-x86/master"
