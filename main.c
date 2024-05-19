#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


#define SAUDACAO_MARIA "Oi Maria!"
#define SAUDACAO_JOSE "Oi José!"
#define SENTE_SE "Sente-se por favor."
#define TCHAU_MARIA "Até mais Maria!"
#define TCHAU_JOSE "Até mais José!"

pthread_cond_t cond_sente_se;
pthread_mutex_t mutex;

int contador = 0;

void * saudacao(void * arg) {

    int id = * (int *) arg;

    while (contador < 5) {
        if (id == 0 && contador == 0) {
            pthread_mutex_lock(&mutex);
            printf("Thread (%d) :", id+1);
            printf(SAUDACAO_MARIA);
            printf("\n");
            contador++;
            pthread_mutex_unlock(&mutex);
            }
        }
        if (id == 1 && contador == 1) {
                pthread_mutex_lock(&mutex);
                printf("Thread (%d) :", id+1);
                printf(SAUDACAO_JOSE);
                printf("\n");
                contador++;
                pthread_cond_signal(&cond_sente_se);
                pthread_mutex_unlock(&mutex);
            }
        }
        else if (id == 2) {
            if (contador < 2) {
                pthread_cond_wait(&cond_sente_se, &mutex);
            }
            else if (contador == 2) {
                pthread_mutex_lock(&mutex);
                contador++;
                printf("Thread (%d) :", id+1);
                printf(SENTE_SE);
                printf("\n");
                pthread_cond_broadcast(&cond_sente_se);
                pthread_mutex_unlock(&mutex);
            }
        }
        else if (id == 3) {
            if (contador < 3) {
                pthread_cond_wait(&cond_sente_se, &mutex);
            } else if (contador == 3) {
                pthread_mutex_lock(&mutex);
                printf("Thread (%d) :", id+1);
                printf(TCHAU_MARIA);
                printf("\n");
                contador++;
                pthread_mutex_unlock(&mutex);
            }
        }
        else if (id == 4) {
            if (contador < 4) {
                pthread_cond_wait(&cond_sente_se, &mutex);
            } else if (contador == 4) {
                pthread_mutex_lock(&mutex);
                printf("Thread (%d) :", id+1);
                printf(TCHAU_JOSE);
                printf("\n");
                contador++;
                pthread_mutex_unlock(&mutex);
            }
        }
    }
    pthread_exit(NULL);
}

void criarThreads(int M) {

    pthread_t tid[M];
    int t, id[M];
    pthread_mutex_init(&mutex, NULL);

    for(t = 0; t < M; t++) {
        id[t]=t;
        if (pthread_create(&tid[t], NULL, saudacao, (void *) &id[t])) {
            printf("--ERRO: pthread_create()\n"), exit(-1);
        }
    }

    for (t=0; t<M; t++) {
        if (pthread_join(tid[t], NULL)) {
            printf("--ERRO: pthread_join() \n"); exit(-1);
        }
    }

    pthread_cond_destroy(&cond_sente_se);
    pthread_mutex_destroy(&mutex);
}

int main(void) {
    int M =  5;
    criarThreads(M);
}