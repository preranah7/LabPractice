
import java.util.*;

class ProcessSJF {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    boolean completed;

    public ProcessSJF(int id, int arrivalTime, int burstTime) {
        this.id = id;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
        this.completed = false;
    }
}

public class SJFNonPreemptive {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Input
        System.out.print("Enter number of processes: ");
        int n = sc.nextInt();

        ProcessSJF[] processes = new ProcessSJF[n];
        for (int i = 0; i < n; i++) {
            System.out.print("Enter arrival time of process " + (i + 1) + ": ");
            int at = sc.nextInt();
            System.out.print("Enter burst time of process " + (i + 1) + ": ");
            int bt = sc.nextInt();
            processes[i] = new ProcessSJF(i + 1, at, bt);
        }

        int time = 0, completed = 0;
        int totalTAT = 0, totalWT = 0;

        while (completed < n) {
            // Find available process with shortest burst time
            int idx = -1, minBT = Integer.MAX_VALUE;
            for (int i = 0; i < n; i++) {
                if (!processes[i].completed && processes[i].arrivalTime <= time) {
                    if (processes[i].burstTime < minBT) {
                        minBT = processes[i].burstTime;
                        idx = i;
                    }
                }
            }

            if (idx == -1) {
                // No process has arrived yet
                time++;
                continue;
            }

            ProcessSJF p = processes[idx];
            time += p.burstTime;
            p.completionTime = time;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;
            p.completed = true;
            completed++;

            totalTAT += p.turnaroundTime;
            totalWT += p.waitingTime;
        }

        // Print result
        System.out.println("\nProcess\tAT\tBT\tCT\tTAT\tWT");
        for (ProcessSJF p : processes) {
            System.out.println("P" + p.id + "\t" + p.arrivalTime + "\t" + p.burstTime +
                    "\t" + p.completionTime + "\t" + p.turnaroundTime + "\t" + p.waitingTime);
        }

        System.out.println("\nAverage Turnaround Time = " + (double) totalTAT / n);
        System.out.println("Average Waiting Time = " + (double) totalWT / n);

        sc.close();
    }
}


// Enter number of processes: 4
// Enter arrival time of process 1: 0
// Enter burst time of process 1: 8
// Enter arrival time of process 2: 1
// Enter burst time of process 2: 4
// Enter arrival time of process 3: 2
// Enter burst time of process 3: 9
// Enter arrival time of process 4: 3
// Enter burst time of process 4: 5

