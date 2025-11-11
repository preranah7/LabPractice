
import java.util.*;

class ProcessFCFS {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;

    public ProcessFCFS(int id, int arrivalTime, int burstTime) {
        this.id = id;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
    }
}

public class FCFS {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Input
        System.out.print("Enter number of processes: ");
        int n = sc.nextInt();

        ProcessFCFS[] processes = new ProcessFCFS[n];
        for (int i = 0; i < n; i++) {
            System.out.print("Enter arrival time of process " + (i + 1) + ": ");
            int at = sc.nextInt();
            System.out.print("Enter burst time of process " + (i + 1) + ": ");
            int bt = sc.nextInt();
            processes[i] = new ProcessFCFS(i + 1, at, bt);
        }

        // Sort by arrival time
        Arrays.sort(processes, Comparator.comparingInt(p -> p.arrivalTime));

        int time = 0;
        int totalTAT = 0, totalWT = 0;

        for (ProcessFCFS p : processes) {
            if (time < p.arrivalTime) {
                time = p.arrivalTime;
            }

            time += p.burstTime;
            p.completionTime = time;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;

            totalTAT += p.turnaroundTime;
            totalWT += p.waitingTime;
        }

        // Print results
        System.out.println("\nProcess\tAT\tBT\tCT\tTAT\tWT");
        for (ProcessFCFS p : processes) {
            System.out.println("P" + p.id + "\t" + p.arrivalTime + "\t" + p.burstTime +
                    "\t" + p.completionTime + "\t" + p.turnaroundTime + "\t" + p.waitingTime);
        }

        System.out.println("\nAverage Turnaround Time = " + (double) totalTAT / n);
        System.out.println("Average Waiting Time = " + (double) totalWT / n);

        sc.close();
    }

}


// Enter number of processes: 3
// Enter arrival time of process 1: 0
// Enter burst time of process 1: 5
// Enter arrival time of process 2: 1
// Enter burst time of process 2: 3
// Enter arrival time of process 3: 2
// Enter burst time of process 3: 8
