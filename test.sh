#!/usr/bin/env bash

mkdir -p test/bin
mkdir -p test/log
printf "compiling test files\n"
c++ -Werror -Wextra -Wall test/vector_test.cpp -o test/bin/std_vec
c++ -Werror -Wextra -Wall -D FT=1 test/vector_test.cpp -o test/bin/ft_vec

c++ -Werror -Wextra -Wall test/map_test.cpp -o test/bin/std_map
c++ -Werror -Wextra -Wall -D FT=1 test/map_test.cpp -o test/bin/ft_map

c++ -Werror -Wextra -Wall test/set_test.cpp -o test/bin/std_set
c++ -Werror -Wextra -Wall -D FT=1 test/set_test.cpp -o test/bin/ft_set

c++ -Werror -Wextra -Wall test/stack_test.cpp -o test/bin/std_stack
c++ -Werror -Wextra -Wall -D FT=1 test/stack_test.cpp -o test/bin/ft_stack

rm test/log/*
printf "generating std logs\n"
test/bin/std_vec >> test/log/std
test/bin/std_map >> test/log/std
test/bin/std_set >> test/log/std
test/bin/std_stack >> test/log/std
printf "generating ft logs\n"
test/bin/ft_vec >> test/log/ft
test/bin/ft_map >> test/log/ft
test/bin/ft_set >> test/log/ft
test/bin/ft_stack >> test/log/ft
printf "showing diff:\n"
diff test/log/std test/log/ft

rm -rf test/log
rm -rf test/bin
