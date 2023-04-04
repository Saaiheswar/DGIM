Language used : c++
Version : c++98

Requirements:
Compiler : G++ Compiler

Step 1: Execute “dgmi.cpp” file in G++ compiler
Execution Input:
Line 1 : Give the bucket size, i.e 32
Line 2:  Give the string as input i.e
In the 1990’s “data mining” was an exciting and popular new concept. Around 2010, people instead started to speak of “big data.” Today, the popular term is “data science.However, during all this time, the concept remained the same: use the most powerful hardware, the most powerful programming systems, and the most efficient algorithms to solve problems in science, commerce, healthcare, government, the humanities, and many other fields of human endeavor.To many, data mining is the process of creating a model from data, often by the process of machine learning, which we mention in Section 1.1.3 and discuss more fully in Chapter 12. However, more generally, the objective of data mining is an algorithm. For instance, we discuss locality-sensitive hashing in Chapter 3 and a number of stream-mining algorithms in Chapter 4, none of which involve a model. Yet in many important applications, the hard part is creating the model, and once the model is available, the algorithm to use the model is straightforward.

Output:
Number of 1’s in the 32 size window, starting from 1st letter of the string to its end.

Explanation:
Functions:

add_timestamp(): Will add timestamps of each bucket end to bucket_timestamps map. We put timestamp1, if both timestamp1 is empty or timestamp1 and timestamp2 are filled, then we merge both timestamp1 and timestamp2 into single timestamp for the next bucket. We put timestamp2, if timestamp1 is filled and timestamp2 is empty.

remove_timestamp(): Will remove timestamps from bucket_timestamps if the end timestamp is out of the window size(32)

Data-Structures:
Map(Ordered Map) :
 bucket_counts = <int,int> => stores  bucket number as key and number of buckets as value
 bucket_timestamps = <int, <int,int>> stores bucket number as key and <timestamp1,timestamp2> as its values (timestamp1: first occurrence end of the bucket, timestamp2 : second occurrence end of the bucket)
 

 

