
import java.util.*;

class Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int turnaroundTime;
    int waitingTime;

    public Process(int id, int arrivalTime, int burstTime, int priority) {
        this.id = id;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
        this.priority = priority;
    }
}

public class PrioritySchedulingNonPreemptive {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Input
        System.out.print("Enter number of processes: ");
        int n = sc.nextInt();

        Process[] processes = new Process[n];
        for (int i = 0; i < n; i++) {
            System.out.print("Enter arrival time of process " + (i + 1) + ": ");
            int at = sc.nextInt();
            System.out.print("Enter burst time of process " + (i + 1) + ": ");
            int bt = sc.nextInt();
            System.out.print("Enter priority of process " + (i + 1) + ": ");
            int pr = sc.nextInt();
            processes[i] = new Process(i + 1, at, bt, pr);
        }

        // Sort by arrival time first
        Arrays.sort(processes, Comparator.comparingInt(p -> p.arrivalTime));

        int time = 0, completed = 0;
        boolean[] isCompleted = new boolean[n];

        while (completed < n) {
            int idx = -1;
            int bestPriority = Integer.MAX_VALUE;

            // Pick process with highest priority among arrived
            for (int i = 0; i < n; i++) {
                if (!isCompleted[i] && processes[i].arrivalTime <= time) {
                    if (processes[i].priority < bestPriority) {
                        bestPriority = processes[i].priority;
                        idx = i;
                    } else if (processes[i].priority == bestPriority) {
                        // If same priority â choose earliest arrival
                        if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                            idx = i;
                        }
                    }
                }
            }

            if (idx != -1) {
                // Execute process
                time += processes[idx].burstTime;
                processes[idx].completionTime = time;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
                isCompleted[idx] = true;
                completed++;
            } else {
                // No process has arrived yet â move time forward
                time++;
            }
        }

        // Print results
        System.out.println("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT");
        int totalTAT = 0, totalWT = 0;
        for (Process p : processes) {
            System.out.println("P" + p.id + "\t" + p.arrivalTime + "\t" + p.burstTime + "\t" + p.priority +
                    "\t" + p.completionTime + "\t" + p.turnaroundTime + "\t" + p.waitingTime);
            totalTAT += p.turnaroundTime;
            totalWT += p.waitingTime;
        }

        System.out.println("\nAverage Turnaround Time = " + (double) totalTAT / n);
        System.out.println("Average Waiting Time = " + (double) totalWT / n);

        sc.close();
    }
}

// Enter number of processes: 4
// Enter arrival time of process 1: 0
// Enter burst time of process 1: 8
// Enter priority of process 1: 2
// Enter arrival time of process 2: 1
// Enter burst time of process 2: 4
// Enter priority of process 2: 1
// Enter arrival time of process 3: 2
// Enter burst time of process 3: 9
// Enter priority of process 3: 3
// Enter arrival time of process 4: 3
// Enter burst time of process 4: 5
// Enter priority of process 4: 2

