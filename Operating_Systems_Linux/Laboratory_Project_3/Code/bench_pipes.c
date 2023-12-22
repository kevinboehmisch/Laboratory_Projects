#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <err.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include "bench_utils.h"


#define MAX_SIZE 16777216 //Maximale Größe von 16MB
#define SLEEP_TIME 1 //Definiert Wartezeit zwischen den Messungen 1s 

int main(int argc, char *argv[])
{
    const int sizes[] = {64, 256, 1024, 4096, 16384, 65536, 262144, 1048576, 4194304, 16777216}; //Array mit den zu testenden Datenmengen
    const int sizes_num = sizeof(sizes) / sizeof(sizes[0]); //Anzahl der Elemente
    int pipefd[2] = {0}; //Array mit Dateideskriptoren für Pipes
    pid_t pid; //Process-ID
    char *buff; //Zeiger auf Speicherbereich
    int ret; //für Rückgabewerte

    for (int i = 0; i < sizes_num; i++) //Hauptschleife, welche solange läuft, bis alle Datenmengen durchlaufen sind 
    {
        ret = pipe(pipefd); //erstellen einer Pipe      
        if (ret == -1) 
        {
            err(EXIT_FAILURE, "pipe");
        }

        pid = getpid(); //Process-ID zuweisen
        pid_t pid_child = fork(); //Child-Prozess wird erstellt, Kopie von Parent
        if (pid_child == -1) 
        {
            err(EXIT_FAILURE, "fork");
        }

        buff = malloc(sizes[i]); //Hier wird entsprechend viel Speicher zu buff allokiert, je nachdem, wie groß der Wert am entsprechenden Array Index ist
        if (buff == NULL) 
        {
            err(EXIT_FAILURE, "malloc");
        }

        if (pid_child == 0) //Überprüfen ob Child Prozess gerade läuft, Child Prozess liest Daten
        {
            int nread = 1; 
            close(pipefd[1]); //Child soll nicht schreiben können nur lesen

            while (nread != 0)
            {
                nread = read(pipefd[0], buff, sizes[i]); //lesen Daten der Pipe durch pipefd[0], an entsprechendem Index von sizes. Kopieren in auf buff gezeigten Speicherbereich, solange nread!=0 ist
            }

            free(buff); //freigeben, da Daten unwichtig sind, es wird nur Leistung der Pipe gemessen
            exit(EXIT_SUCCESS);
        }
        else //Ansonsten der Elternprozess
        {
            int *ticks = malloc(MEASUREMENTS * sizeof(int)); // Zeiger auf Anfang des allokierten Speicherbereichs
            if (ticks == NULL)
            {
                err(EXIT_FAILURE, "malloc");
            }

            memset(ticks, 0, MEASUREMENTS * sizeof(int)); //es werden 0en gesetzt im Array ticks
            int min_ticks; //mindestanzahl an CPU Zyklen die für einen Prozess, also hier schreiben in eine Pipe benötigt werden
            int max_ticks;
            long long ticks_all; //Gesamte Anzahl an CPU Zyklen
            struct timeval tv_start; //Struct speichert Zeitpunkt an dem Messung beginnt
            struct timeval tv_stop; //Zeitpunkt an dem Messungen enden
            double time_delta_sec; //speicher dauer der Messungen in Sekunden

            sleep(SLEEP_TIME); //Pause 1s

            gettimeofday(&tv_start, NULL); //Startzeit in struct tv_start speichern
            close(pipefd[0]); //Elternprozess darf nicht lesen

            for (int j = 0; j < MEASUREMENTS; j++) 
            {
                unsigned long long start = getrdtsc(); //Anzahl der CPU Zyklen seit Start wird in start gespeichert

                ret = write(pipefd[1], buff, sizes[i]); //Inhalt von buff wird mit Größe an Index i aus sizes in pipe geschrieben, ret enthält also Anzahl geschriebener Bytes
                if (ret != sizes[i]) // die Anzahl der geschriebenen Bytes, ret, muss dem Wert aus sizes entsprechen, ansonsten Fehler
                {
                    perror("write");
                    exit(EXIT_FAILURE);
                }

                unsigned long long stop = getrdtsc(); //nach schreiben in die Pipe erneut rdtsc abfragen und in stop speichern
                ticks[j] = stop - start; //Differenz aus start-stop gibt die Anzahl der CPU Zyklen für den Prozess, des schreibens in eine Pipe zurück
            }

            gettimeofday(&tv_stop, NULL); // Endzeitpunkt nach Schreiben in der Pipe wird in tv_stop gespeichert

            min_ticks = INT_MAX;  //standardwerte für min_ticks, max_ticks, ticks_all festlegen, welche in der Schleife aktualisiert werden
            max_ticks = INT_MIN;
            ticks_all = 0;
            for (int j = 0; j < MEASUREMENTS; j++)
            {
                if (min_ticks > ticks[j]) //solange min_ticks größer ist wird aktualisert, sodass man minimum erhält
                {
                    min_ticks = ticks[j];
                }
                if (max_ticks < ticks[j]) //solange max_ticks kleiner ist wird aktualisiert, bis maximum erreicht ist, da man ja beim minimum gestartet hat
                {
                    max_ticks = ticks[j];
                }
                ticks_all += ticks[j]; //summe aller ticks
            }
            ticks_all -= min_ticks;
            ticks_all -= max_ticks;

            time_delta_sec = ((tv_stop.tv_sec - tv_start.tv_sec) + ((tv_stop.tv_usec - tv_start.tv_usec) / (1000.0 * 1000.0))); //berechnen der zeit für das Schreiben in die Pipe in Sekunden

            printf("PID:%d time: min:%d max:%d Ticks Avg without min/max:%f Ticks (for %d measurements) for %d Bytes (%.2f MB/s)\n",
                   pid, min_ticks, max_ticks,
                   (double)ticks_all / (MEASUREMENTS - 2.0), MEASUREMENTS, sizes[i],
                   ((double)sizes[i] * MEASUREMENTS) / (1024.0 * 1024.0 * time_delta_sec)); 

            close(pipefd[1]); //das schreiben wird am Ende für den Parent Prozess gesperrt
            free(ticks); //Speicherplatz wird geräumt
        }
        free(buff);
   }
   exit(EXIT_SUCCESS);
}

