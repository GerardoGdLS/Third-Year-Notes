#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define min(a,b) (((a)<(b))?(a):(b))

// total jobs
int numofjobs = 0;

typedef struct job  {
    int id;
    int arrival;
    int length;
    int tickets; // number of tickets for lottery scheduling
    // TODO: add any other metadata you need to track here
    int original_length;
    int start_time;
    int completion_time;
    int time_last_ran;
    int wait_time;
    struct job *next;
}Job;

// the workload list
struct job *head = NULL;

void free_jobs(Job **head_pointer) {
    
    Job *current = *head_pointer;
    Job *next_job;

    while (current != NULL) {

        next_job = current->next; 
        free(current);            
        current = next_job;       
    }

    *head_pointer = NULL; // Set head_pointer to NULL after freeing
}

Job* copy_job_list(Job* head) {
    if (head == NULL) return NULL;

    Job* copy_head = NULL;
    Job* current_copy = NULL;

    Job* current = head;
    while (current != NULL) {
        
        Job* new_job = (Job*) malloc(sizeof(Job));
        new_job->id = current->id;
        new_job->arrival = current->arrival;
        new_job->length = current->length;
        new_job->start_time = -1; 
        new_job->completion_time = -1; 
        new_job->next = NULL;

        if (copy_head == NULL) {
            copy_head = new_job;
            current_copy = copy_head;
        } else {
            current_copy->next = new_job;
            current_copy = new_job;
        }

        current = current->next;
    }

    return copy_head;
}

void append_to(Job **head_pointer, int arrival, int length, int tickets){

    // TODO: create a new job and init it with proper data


    Job *newj = (Job*)malloc(sizeof(Job));
    if (newj == NULL){
        perror("Failed to allocate memory for new job");
        exit(EXIT_FAILURE);
    }
    newj->id = numofjobs++;
    newj->arrival = arrival;
    newj->length = length;
    newj->tickets = tickets;
    newj-> start_time = -1;
    newj -> wait_time = 0;
    newj -> time_last_ran = 0;
    newj->next = NULL;
    newj->length = length;
    newj->original_length = length; 

    if(*head_pointer == NULL){ //List is empty
        *head_pointer = newj;
        return;
    }

    //We traverse the list to add last
    Job * current = *head_pointer;
    while(current->next != NULL){
        current = current->next;
    }

    current->next = newj;

    return;
}

void read_job_config(const char* filename)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int tickets  = 0;

    char* delim = ",";
    char *arrival = NULL;
    char *length = NULL;

    // TODO, error checking
    fp = fopen(filename, "r");
    if (fp == NULL){
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }
    // TODO: if the file is empty, we should just exit with error

    int count = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {   count+=1;
        if( line[read-1] == '\n' )
            line[read-1] =0;
        arrival = strtok(line, delim);
        length = strtok(NULL, delim);
        tickets += 100;

        append_to(&head, atoi(arrival), atoi(length), tickets);
    }

    if (count == 0){
        fprintf(stderr, "Error: File is empty\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }


    fclose(fp);
    if (line) free(line);
}


void policy_SJF(int analysis) {
    printf("Execution trace with SJF:\n");

    Job* current = head;
    Job* queue = NULL;
    int current_time = 0;

    // I create a copy of the list so we can maintain the order for the analysis section
    Job* job_list_copy = copy_job_list(current);

    while (job_list_copy != NULL || queue != NULL) {

        while (job_list_copy != NULL && job_list_copy->arrival <= current_time) {
            Job* job_to_add = job_list_copy;
            job_list_copy = job_list_copy->next;

            if (queue == NULL || job_to_add->length < queue->length || 
                (job_to_add->length == queue->length && job_to_add->arrival < queue->arrival)) {
                job_to_add->next = queue;
                queue = job_to_add;
            } else {
                Job* temp = queue;
                while (temp->next != NULL && 
                       (temp->next->length < job_to_add->length || 
                        (temp->next->length == job_to_add->length && temp->next->arrival < job_to_add->arrival))) {
                    temp = temp->next;
                }
                job_to_add->next = temp->next;
                temp->next = job_to_add;
            }
        }

        if (queue == NULL && job_list_copy != NULL) {
            current_time = job_list_copy->arrival;
            continue;
        }

        Job* job_to_run = queue;
        queue = queue->next;

        if (job_to_run->start_time == -1) {
            job_to_run->start_time = current_time;
        }

        printf("t=%d: [Job %d] arrived at [%d], ran for: [%d]\n",
               current_time, job_to_run->id, job_to_run->arrival, job_to_run->length);

        current_time += job_to_run->length;
        job_to_run->completion_time = current_time;

        Job* original_job = head;
        while (original_job != NULL) {
            if (original_job->id == job_to_run->id) {
                original_job->start_time = job_to_run->start_time;
                original_job->completion_time = job_to_run->completion_time;
                break;
            }
            original_job = original_job->next;
        }
    }

    printf("End of execution with SJF.\n");

    if (analysis == 1) {
        printf("Begin analyzing SJF:\n");

        current = head; 
        int total_response = 0;
        int total_turnaround = 0;
        int total_wait = 0;

        while (current != NULL) {
            int arrival = current->arrival;
            int start = current->start_time;
            int completion = current->completion_time;

            int response_time = start - arrival;
            int turn_around = completion - arrival;
            int wait_time = start - arrival;

            total_response += response_time;
            total_turnaround += turn_around;
            total_wait += wait_time;

            printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n",
                   current->id, response_time, turn_around, wait_time);

            current = current->next;
        }

        double avg_response = (double)total_response / numofjobs;
        double avg_turnaround = (double)total_turnaround / numofjobs;
        double avg_wait = (double)total_wait / numofjobs;

        printf("Average -- Response: %.2f  Turnaround %.2f  Wait %.2f\n",
               avg_response, avg_turnaround, avg_wait);

        printf("End analyzing SJF.\n");
    }

    free_jobs(&job_list_copy);
}


void policy_STCF() {
    printf("Execution trace with STCF:\n");

    int current_time = 0;
    int jobs_to_do = numofjobs;

    while (jobs_to_do > 0) {
        Job *job = head;
        Job *next_job = NULL;
        int shortest_remaining = INT_MAX;

        // Find the job with the shortest remaining time that has arrived
        while (job != NULL) {
            if (job->arrival <= current_time && job->length > 0 && job->length < shortest_remaining) {
                shortest_remaining = job->length;
                next_job = job;
            }
            job = job->next;
        }

        if (next_job != NULL) {
            // If the job is starting for the first time, set the start time
            if (next_job->start_time == -1) {
                next_job->start_time = current_time;
                next_job->wait_time = current_time - next_job->arrival;
            }

            // Run the job for as long as no new job arrives to preempt it
            int time_to_run = next_job->length;

            // Check if a new job arrives and preempts the current job
            job = head;
            while (job != NULL) {
                if (job->arrival > current_time && job->arrival < current_time + time_to_run) {
                    time_to_run = job->arrival - current_time;  // Preempt current job early
                    break;
                }
                job = job->next;
            }

            // Run the selected job for the determined amount of time
            printf("t=%d: [Job %d] arrived at [%d], ran for: [%d]\n", current_time, next_job->id, next_job->arrival, time_to_run);

            // Advance the current time and reduce the job's remaining length
            next_job->length -= time_to_run;
            current_time += time_to_run;

            // If the job is completed, set its completion time and reduce jobs left
            if (next_job->length == 0) {
                next_job->completion_time = current_time;
                jobs_to_do--;
            }
        } else {
            // No job is ready, advance the time
            current_time++;
        }
    }

    printf("End of execution with STCF.\n");
}

void STCF_analysis() {
    printf("Begin analyzing STCF:\n");

    Job *current = head;
    int total_response = 0;
    int total_turnaround = 0;
    int total_wait = 0;

    while (current != NULL) {
        int arrival = current->arrival;
        int start = current->start_time;
        int completion = current->completion_time;

        int response_time = start - arrival;
        int turnaround_time = completion - arrival;

        // Correct wait time is the total time job spent waiting in the queue
        int wait_time = turnaround_time - current->original_length;

        total_response += response_time;
        total_turnaround += turnaround_time;
        total_wait += wait_time;

        printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n", 
                current->id, response_time, turnaround_time, wait_time);

        current = current->next;
    }

    double avg_response = (double)total_response / numofjobs;
    double avg_turnaround = (double)total_turnaround / numofjobs;
    double avg_wait = (double)total_wait / numofjobs;

    printf("Average -- Response: %.2f  Turnaround %.2f  Wait %.2f\n", 
           avg_response, avg_turnaround, avg_wait);

    printf("End analyzing STCF.\n");
}

void policy_RR(int slice, int analysis)
{
    printf("Execution trace with RR:\n");
    Job *current = head;
    Job *queue_head = head;
    Job * queue_tail = head;
    Job * queue_current = head;
    int queue_length = 0;
    int current_time = 0;
    int jobs_to_do = numofjobs;
    
    while (current !=  NULL || queue_length > 0 ){
        if (current !=NULL){
            int arrival = current->arrival;


        // if job has arrived, then add to queue
            if (arrival <= current_time){
            
                queue_tail = current;
                current = current->next;
                queue_length+=1;
            
            }
        }
        if (queue_current == queue_tail){
            queue_current = queue_head;
        } else {
            queue_current =  queue_current->next;  
    
    }
        int time_ran = 0;
        if (queue_length == 0 && jobs_to_do > 0){
            current_time +=1;
        }

            //running jobs on the queue
        if (queue_current->length > 0){
            if (queue_current->start_time == -1){
                queue_current->start_time = current_time;
                queue_current->wait_time += (current_time - queue_current->arrival);
            } else {
                queue_current->wait_time += (current_time - queue_current->time_last_ran);
            }
            int time_remaining = queue_current->length;
            time_ran = slice; //default
            queue_current->length -= slice;
            
            if (time_remaining <= slice){
                time_ran = time_remaining;
                queue_length-=1;
                queue_current ->completion_time = current_time + time_ran;
                jobs_to_do-=1;


                }
            printf("t=%d: [Job %d] arrived at [%d], ran for: [%d]\n", current_time, queue_current->id, queue_current->arrival,time_ran);
            current_time += time_ran;
            queue_current->time_last_ran = current_time;

        }
       

    }
    printf("End of execution with RR.\n");
   
    if (analysis == 1){
        printf("Begin analyzing RR:\n");
        current = head;
        int total_response = 0;
        int total_turnaround = 0;
        int total_wait = 0;

        while(current != NULL){
            int arrival = current->arrival;
            int start = current ->start_time;
            int completion = current -> completion_time;

            int response_time = start - arrival;
            int turn_around = completion - arrival;

            total_response += response_time;
            total_turnaround += turn_around;
            total_wait += current->wait_time;

            printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n", current->id, response_time, turn_around, current->wait_time);
            current = current->next;
    }
    
        double avg_response = (double)total_response / (numofjobs);
        double avg_turnaround = (double)total_turnaround / (numofjobs);
        double avg_wait = (double) total_wait /(numofjobs);
        printf("Average -- Response: %.2f  Turnaround %.2f  Wait %.2f\n", avg_response, avg_turnaround, avg_wait);


        printf("End analyzing RR.\n");
    
    }

    return;


}

void policy_LT(int slice) {
    printf("Execution trace with LT:\n");

    srand(42);  // Ensures deterministic behavior

    int total_tickets;
    int current_time = 0;
    int jobs_to_do = numofjobs;

    // Find the first job's arrival time to start
    Job *job = head;
    current_time = head->arrival;  // Start current time at the first job's arrival time

    while (jobs_to_do > 0) {
        total_tickets = 0;
        job = head;

        // Recalculate the total tickets from jobs that have arrived and still have work to do
        while (job != NULL) {
            if (job->length > 0 && job->arrival <= current_time) {
                total_tickets += job->tickets;
            }
            job = job->next;
        }

        // If no job is available yet, advance the current time to the next job's arrival time
        if (total_tickets == 0) {
            int next_arrival = INT_MAX;
            job = head;
            while (job != NULL) {
                if (job->length > 0 && job->arrival > current_time) {
                    next_arrival = min(next_arrival, job->arrival);
                }
                job = job->next;
            }
            current_time = next_arrival;
            continue;  // Skip to the next loop iteration after advancing the time
        }

        // Select a random winning ticket from the available jobs
        int winning_ticket = rand() % total_tickets;
        int ticket_counter = 0;
        Job *selected_job = NULL;
        job = head;

        // Traverse the job list to find the job corresponding to the winning ticket
        while (job != NULL) {
            if (job->length > 0 && job->arrival <= current_time) {
                ticket_counter += job->tickets;
                if (ticket_counter > winning_ticket) {
                    selected_job = job;
                    break;
                }
            }
            job = job->next;
        }

        if (selected_job != NULL) {
            // If the job is starting for the first time, set the start time
            if (selected_job->start_time == -1) {
                selected_job->start_time = current_time;
                selected_job->wait_time = current_time - selected_job->arrival;
            }

            int time_to_run = min(slice, selected_job->length);  // Run for at most 'slice' ticks
            selected_job->length -= time_to_run;

            printf("t=%d: [Job %d] arrived at [%d], ran for: [%d]\n", current_time, selected_job->id, selected_job->arrival, time_to_run);

            current_time += time_to_run;

            // If the job is finished, reduce job count and update its completion time
            if (selected_job->length == 0) {
                selected_job->completion_time = current_time;
                jobs_to_do--;
            }
        }
    }

    printf("End of execution with LT.\n");
}




void LT_analysis() {
    printf("Begin analyzing LT:\n");

    Job *current = head;
    int total_response = 0;
    int total_turnaround = 0;
    int total_wait = 0;

    while (current != NULL) {
        int arrival = current->arrival;
        int start = current->start_time;
        int completion = current->completion_time;

        int response_time = start - arrival;
        int turnaround_time = completion - arrival;
        int wait_time = turnaround_time - current->original_length;

        total_response += response_time;
        total_turnaround += turnaround_time;
        total_wait += wait_time;

        printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n", 
               current->id, response_time, turnaround_time, wait_time);

        current = current->next;
    }

    double avg_response = (double)total_response / numofjobs;
    double avg_turnaround = (double)total_turnaround / numofjobs;
    double avg_wait = (double)total_wait / numofjobs;

    printf("Average -- Response: %.2f  Turnaround %.2f  Wait %.2f\n", 
           avg_response, avg_turnaround, avg_wait);

    printf("End analyzing LT.\n");
}


void FIFO_analysis(){
    printf("Begin analyzing FIFO:\n");
    Job *current = head;
    int current_time = 0;
    int total_response = 0;
    int total_turnaround = 0;

    while(current != NULL){
        int arrival = current->arrival;
        int start = current_time >= arrival ? current_time : arrival;
        int completion = start + current->length;

        int response_time = start - arrival;
        int turn_around = completion - arrival;

        total_response += response_time;
        total_turnaround += turn_around;

       printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n", current->id, response_time, turn_around, response_time);
        current_time = completion; 
        current = current->next;
    }
    
    double avg_response = (double)total_response / (numofjobs);
    double avg_turnaround = (double)total_turnaround / (numofjobs);

    printf("Average -- Response: %.2f  Turnaround %.2f  Wait %.2f\n", avg_response, avg_turnaround, avg_response);

    printf("End analyzing FIFO.\n");    
    return;
}


void policy_FIFO(){
    printf("Execution trace with FIFO:\n");
    Job *current = head;
    int current_time = 0;
    while (current != NULL){
        if (current_time < current->arrival){
         current_time = current->arrival;
        }

        printf("t=%d: [Job %d] arrived at [%d], ran for: [%d]\n", current_time, current->id, current->arrival, current->length);
        current_time += current->length;
        current = current->next;
    }

    printf("End of execution with FIFO.\n");
}


int main(int argc, char **argv){

    static char usage[] = "usage: %s analysis policy slice trace\n";

    int analysis;
    char *pname;
    char *tname;
    int slice;


    if (argc < 5)
    {
        fprintf(stderr, "missing variables\n");
        fprintf(stderr, usage, argv[0]);
		exit(1);
    }

    // if 0, we don't analysis the performance
    analysis = atoi(argv[1]);

    // policy name
    pname = argv[2];

    // time slice, only valid for RR
    slice = atoi(argv[3]);

    // workload trace
    tname = argv[4];

    read_job_config(tname);

    if (strcmp(pname, "FIFO") == 0)
    {
        policy_FIFO();
        if (analysis == 1){
            FIFO_analysis();
            // TODO: perform analysis
        }
    }
    else if (strcmp(pname, "SJF") == 0)
    {
        policy_SJF(analysis);
    }
    else if (strcmp(pname, "STCF") == 0)
    {
        policy_STCF();  // Run the STCF policy
        if (analysis == 1) {  // Perform analysis if required
            STCF_analysis();
        }
    }
    else if (strcmp(pname, "RR") == 0)
    {
        policy_RR(slice, analysis);
    }
    else if (strcmp(pname, "LT") == 0)
    {
        policy_LT(slice);  // Run the LT policy
        if (analysis == 1) {  // Perform analysis if required
            LT_analysis();
        }
    }

    free_jobs(&head);
  
}