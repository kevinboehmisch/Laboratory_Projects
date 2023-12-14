#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kevin Böhmisch");
MODULE_DESCRIPTION("Latency Module");



static void work_handler(struct work_struct *w);

static struct workqueue_struct *wq = NULL; //Zeiger Workqueue-Struktur, enthält Abfolge aller Funktionen
static DECLARE_DELAYED_WORK(dwork, work_handler); //deklariert den delayed_work struct und übergibt die Funktion (work_handler), sowie Struct (Adresse von dwork) in dem die Funktion rein soll
static unsigned long delay;

static int DELAY_MS = 50; // Standardwert von 10000 Millisekunden
module_param(DELAY_MS, int, 0); //Übergabeparameter DELAY_MS
MODULE_PARM_DESC(DELAY_MS, "Delay after which the task is repeated in milliseconds (Default Delay: 10000ms)");



static void work_handler(struct work_struct *w) {
    printk(KERN_INFO "Backtrace                   Count            Time            Max");
        for(int i=0; i<current->latency_record_count;i++){
            printk(KERN_INFO "%pX       %10.u      %10.lu     %10.lu \n", (void*)current->latency_record[i].backtrace[0], current->latency_record[i].count, current->latency_record[i].time/1000,  current->latency_record[i].max);
    }
    printk(KERN_INFO "\n");
    queue_delayed_work(wq, &dwork, delay); //der work_handler wird dadurch kontinuierlich ausgeführt, da er während dem Funktionsaufruf, wieder erneut aufgerufen wird
}

__init int init_module(void) {
    printk(KERN_ALERT "MODULE STARTED");
    delay = msecs_to_jiffies(DELAY_MS); 
    if(DELAY_MS<10){
        pr_err("invalid Parameter");
        return -1;
    }
    wq = alloc_workqueue("latency", WQ_UNBOUND, 1); //erstellen einer workqueue
    if (NULL == wq) {
        pr_err("Failed to create work queue\n");
        return -1;
    }
    queue_delayed_work(wq, &dwork, delay); //ausführen der workqueue, nach dem Ablauf des delays
    return 0;
}

__exit void cleanup_module(void){ 
    printk(KERN_ALERT "MODULE REMOVED");
    cancel_delayed_work_sync(&dwork); //geschedulde Prozesse in der Warteschleife werden beendet
    destroy_workqueue(wq); //löschen der workqueue
}




