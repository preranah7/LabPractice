
import java.util.*;

class Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;

    public Process(int id, int arrivalTime, int burstTime) {
        this.id = id;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
        this.remainingTime = burstTime;
    }
}

public class RoundRobinScheduling {
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
            processes[i] = new Process(i + 1, at, bt);
        }

        System.out.print("Enter Time Quantum: ");
        int tq = sc.nextInt();

        // Sort by arrival time
        Arrays.sort(processes, Comparator.comparingInt(p -> p.arrivalTime));

        Queue<Process> readyQueue = new LinkedList<>();
        int time = 0;
        int completed = 0;
        boolean[] visited = new boolean[n];

        // Add first process to queue
        readyQueue.add(processes[0]);
        visited[0] = true;
        time = processes[0].arrivalTime;

        while (!readyQueue.isEmpty()) {
            Process current = readyQueue.poll();

            if (current.remainingTime > tq) {
                // Run for time quantum
                time += tq;
                current.remainingTime -= tq;
            } else {
                // Finish process
                time += current.remainingTime;
                current.remainingTime = 0;
                current.completionTime = time;
                current.turnaroundTime = current.completionTime - current.arrivalTime;
                current.waitingTime = current.turnaroundTime - current.burstTime;
                completed++;
            }

            // Add newly arrived processes to queue
            for (int i = 0; i < n; i++) {
                if (!visited[i] && processes[i].arrivalTime <= time) {
                    readyQueue.add(processes[i]);
                    visited[i] = true;
                }
            }

            // If current not finished, push back
            if (current.remainingTime > 0) {
                readyQueue.add(current);
            }

            // If queue is empty but processes remain, jump to next arrival
            if (readyQueue.isEmpty() && completed < n) {
                for (int i = 0; i < n; i++) {
                    if (!visited[i]) {
                        time = processes[i].arrivalTime;
                        readyQueue.add(processes[i]);
                        visited[i] = true;
                        break;
                    }
                }
            }
        }

        // Print results
        System.out.println("\nProcess\tAT\tBT\tCT\tTAT\tWT");
        int totalTAT = 0, totalWT = 0;
        for (Process p : processes) {
            System.out.println("P" + p.id + "\t" + p.arrivalTime + "\t" + p.burstTime +
                    "\t" + p.completionTime + "\t" + p.turnaroundTime + "\t" + p.waitingTime);
            totalTAT += p.turnaroundTime;
            totalWT += p.waitingTime;
        }

        System.out.println("\nAverage Turnaround Time = " + (double) totalTAT / n);
        System.out.println("Average Waiting Time = " + (double) totalWT / n);

        sc.close();
    }
}