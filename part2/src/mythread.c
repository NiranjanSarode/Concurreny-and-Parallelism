    #include<stdio.h>
    #include<stdlib.h>
    #include<ucontext.h>
    #include<signal.h>
    #include<sys/time.h>
    #include<unistd.h>
    #include "../include/mythread.h"
    #include "../include/hm.h"
    #define MEM 6400

    static ucontext_t ctx;

    struct listentry* current_thread; 

    struct list* thread_list;



    void mythread_init() {
        thread_list = list_new();
        getcontext(&ctx);
        list_add(thread_list,&ctx);
        current_thread= thread_list->head;
    }


    ucontext_t* mythread_create(void (*func)(void*), void* arg) {
        
        ucontext_t* new_con = (ucontext_t*)malloc(sizeof(ucontext_t));
        char *stack = (char *)malloc(MEM*sizeof(char));
        getcontext(new_con);
        new_con->uc_stack.ss_sp = stack;
        new_con->uc_stack.ss_size = MEM;
        new_con->uc_link = &ctx;
        char* filename = arg;
        makecontext(new_con,func,1,arg);
        if(new_con != NULL){            
            list_add(thread_list,new_con);
        }
        return new_con;
    }



    void mythread_join() {
        while(thread_list->head->next!=NULL){
            current_thread = thread_list->head->next;
            swapcontext(&ctx,thread_list->head->next->data);
            list_rm(thread_list,current_thread);
        }
    }




    void mythread_yield() {
        if (current_thread->next!=NULL){
            current_thread = current_thread->next;
            swapcontext(current_thread->prev->data, current_thread->data);
        }
        else{
            current_thread = thread_list->head->next;
            swapcontext(thread_list->tail->data, current_thread->data);
        }

    }

    struct lock* lock_new(){
        struct lock* new_lock = (struct lock*)malloc(sizeof(struct lock));
        new_lock->ctx = NULL;
        return new_lock;
    }

    void lock_acquire(struct lock* lk){
        while(lk->ctx != NULL){
            mythread_yield();
        }
        lk->ctx = current_thread->data;
    }

    int lock_release(struct lock* lk){
        lk->ctx = NULL;
    }
