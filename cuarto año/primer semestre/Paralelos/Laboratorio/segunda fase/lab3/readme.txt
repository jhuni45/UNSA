como compilar

gcc -o mutex pth_pi_mutex.c -lpthread

gcc -o busy pth_pi_busy_wait.c -lpthread

gcc -o vector pth_mat_vect.c -lpthread

gcc -o lista threaded_list.c my_rand.c -lpthread


como ejecutar

./mutex 64 100000000

./busy 64 100000000

./vector 8
