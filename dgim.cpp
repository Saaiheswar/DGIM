// Consider the following paragraph of texts:
// “In the 1990’s “data mining” was an exciting and popular new concept. Around 2010, people
// instead started to speak of “big data.” Today, the popular term is “data science.” However,
// during all this time, the concept remained the same: use the most powerful hardware, the most
// powerful programming systems, and the most efficient algorithms to solve problems in science,
// commerce, healthcare, government, the humanities, and many other fields of human endeavor.
// To many, data mining is the process of creating a model from data, often by the process of
// machine learning, which we mention in Section 1.1.3 and discuss more fully in Chapter 12.
// However, more generally, the objective of data mining is an algorithm. For instance, we discuss
// locality-sensitive hashing in Chapter 3 and a number of stream-mining algorithms in Chapter 4,
// none of which involve a model. Yet in many important applications, the hard part is creating the
// model, and once the model is available, the algorithm to use the model is straightforward.”
// Generate a 1/0 stream from the above paragraph as follows:
// 1. Ignore all non-letter characters such as digits, dots, and spaces.
// 2. Convert each letter to its ASCII code (integer). You can refer to the following link for the
// ASCII table for conversion: https://www.asciitable.com/.
// 3. If the converted ASCII code is an odd number, the corresponding bit is 1; otherwise, the
// corresponding bit is 0.
// 4. The stream starts from the first letter and ends at the last letter.
// You are asked to implement the DGIM algorithm with N = 32. Suppose your current bit is
// corresponding to the first letter (‘s”) of the last word (“straightforward“) in the paragraph.
// Construct the buckets and estimate the number of 1’s using the sliding window of given size (N
// = 32) for the current bit. Your DGIM algorithm should continue to estimate the number of 1’s
// by taking new bits corresponding to the rest of the letters of the same word. Each new bit
// would generate a new count.

// Input: The input file contains the following information:
// 1. The first line contains the size of the sliding window (N = 32).
// 2. The second line contains the string
// Output: The output file contains the estimated number of 1’s for each new bit in the stream.
 

#include <bits/stdc++.h>
#include <vector>
//#define TxtIO   freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
using namespace std;
int add_timestamp(map<int, pair<int,int> > &bucket_timestamps,map<int,int> &bucket_counts, int timestamp,int bucket){ //adds timestamp to bucket and returns timestamp of next bucket
    int timestamp_next_bucket = bucket_timestamps[bucket].second;
    if((bucket_timestamps[bucket].first == 0 && bucket_timestamps[bucket].second == 0) || (bucket_timestamps[bucket].first != 0 && bucket_timestamps[bucket].second != 0))
    {
        bucket_timestamps[bucket].first = timestamp;
        bucket_timestamps[bucket].second = 0;
    }
    else if(bucket_timestamps[bucket].first != 0 && bucket_timestamps[bucket].second == 0){
        bucket_timestamps[bucket].second = timestamp;
    }
    if(timestamp_next_bucket != 0 ) {
        bucket_counts[bucket*2]++;
        bucket_counts[bucket] = 1;
    }
    return timestamp_next_bucket;
}
void remove_bucket_timestamp(map<int, pair<int,int> > &bucket_timestamps, int bucket){ //removes bucket timestamp from bucket_timestamps if buckets timestamp exceeds the bucket size
    if(bucket_timestamps[bucket].first != 0 && bucket_timestamps[bucket].second != 0){
    bucket_timestamps[bucket].first = bucket_timestamps[bucket].second;
    bucket_timestamps[bucket].second = 0;
    }
    else if(bucket_timestamps[bucket].first != 0 && bucket_timestamps[bucket].second == 0){
        bucket_timestamps.erase(bucket);
    }
}
/*void print_map(map<int, int> &bucket_counts){
    for(map<int, int >::iterator it = bucket_counts.begin(); it != bucket_counts.end(); it++){
        cout<<it->first<<" "<<it->second<<endl;
    }
}
void print_map_timestamp(map<int, pair<int,int> > &bucket_timestamps){
    for(map<int, pair<int,int> >::iterator it = bucket_timestamps.begin(); it != bucket_timestamps.end(); it++){
        cout<<it->first<<" "<<it->second.first<<" "<<it->second.second<<endl;
    }
}*/
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int N;
    cin >> N;
    string s;
    while (getline(cin, s)){}
    int n = s.size();
    vector<int> a;
    int cnt=0;
    for(int i = 0; i < n; i++){
        if(isalpha(s[i])){
            if((s[i]-'0') & 1){
                a.push_back(1);
            }
            else{
                a.push_back(0);
            }
        }
    }
    int timestamp = 1;
    map<int, int> bucket_counts; //<bucket, count>
    map<int, pair<int,int> > bucket_timestamps; //<bucket, <timestamp1, timestamp2>>
    int bucket_index_merge = 0;
    int siz = a.size();
    for(int i=0;i<siz;i++,timestamp++){
        //check if bucket_timestamp is empty
        //remove two timestamps from bucket_timestamps if present for bucket 1, and add timestamp.
        if(!bucket_timestamps.empty()){
           map<int, pair<int,int> >::iterator end_bucket = bucket_timestamps.end();
           end_bucket--;
           int end_timestamp = end_bucket->second.first;
           if(timestamp - end_timestamp >= N){ //remove the last element from list and bucket_timestamps if its timestamp is greater than N
                bucket_counts[end_bucket->first]--;
                if(bucket_counts[end_bucket->first] == 0){
                    bucket_counts.erase(end_bucket->first);
                }
                remove_bucket_timestamp(bucket_timestamps,end_bucket->first);
           }
           }
        if(a[i] == 1){
           bucket_counts[1]++;
           //loop over bucket_counts and merge buckets if count is greater than 2
              for(map<int, int >::iterator it = bucket_counts.begin(); it != bucket_counts.end(); it++){
                if(it->first == 1){
                    bucket_index_merge = add_timestamp(bucket_timestamps,bucket_counts,timestamp,it->first);
                }
                else if(it->first != 1 && bucket_index_merge != 0){
                    bucket_index_merge = add_timestamp(bucket_timestamps,bucket_counts,bucket_index_merge,it->first);
                }
                else break;
            }
        }
        int count = 0;
        for(map<int, int>::iterator it = bucket_counts.begin(); it != bucket_counts.end(); it++){
            if(next(it) == bucket_counts.end()){
                count += ((it->first)/2);
                break;
            }
            count += (it->first * it->second);
            }
        cout << count << endl;
        }
    return 0;
}
