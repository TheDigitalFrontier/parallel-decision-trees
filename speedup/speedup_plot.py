#!/usr/bin/python

# Import necessary packages
import matplotlib.pyplot as plt

# Record elapsed time in seconds as provided by time function
serial = [12, 22, 32, 42]
parallel = [8,7,6,5]

# Calculate speedup
speedup = [serial[i] / parallel[i] for i in range(4)]
k = [1,2,3,4] # This will vary depending on parallelization you're using

# Plot Speedup Chart
plt.figure(figsize=(12,8))
plt.ylim(0,9)
plt.plot(k, speedup, label="", lw=5, c="blue")
plt.ylabel("Speedup T(1) / T(p)", size=20)
plt.xlabel("Parallel nodes utilized", size=20)
plt.title("Speed Up Achieved From ??????", size=20)
plt.show()
