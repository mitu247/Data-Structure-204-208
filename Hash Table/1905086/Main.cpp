#include<bits/stdc++.h>
#include<ctime>
#include "HashT.cpp"
#include "HashL.cpp"
#include "HashQ.cpp"
#include "HashD.cpp"
using namespace std::chrono;
vector<string> words;
vector<pair<string,int>>unique_word;
vector<vector<pair<string,int>>> words_lf;
vector<vector<pair<string,int>>> words_del;
vector<vector<pair<string,int>>> words_srh;
vector<vector<pair<string,int>>>words_delsrh;
string str_gen(){
    string str;
    char c;
    int r;
    //srand (time(0));
    for (int i=0; i<7; i++)
    {    r = rand() % 26;
          c = 'a' + r;
          str.push_back(c);
    }
    return str;
}
bool search_duplicate(string new_str){
    if(words.size()==0) return false;
    for(int i=0; i<words.size();i++){
        if(words[i]==new_str)
        {
            return true;
        }
    }
    return false;
}

void unique_word_generation(int n){
    string test_str;
    for(int i = 0; i<n; i++){
        test_str = str_gen();
        if(!search_duplicate(test_str)){
        words.push_back(test_str);
        }
     }
     for(int i = 0; i<words.size(); i++){
        unique_word.push_back({words[i],i+1});
     }
}

vector<pair<string,int>>word_genLF(double LF) {
    vector<pair<string,int>> tmp;
    int lf_size = LF*unique_word.size();

    for (int i=0; i<lf_size; i++) {
        int idx = rand() % (unique_word.size());
        tmp.push_back(unique_word[idx]);
    }

    return tmp;
}
void final_word_generation(){
    double LF = 0.4;
    for (int i=0; i<=5; i++) {
        words_lf[i] = word_genLF(LF);
        LF += 0.1;
    }
}
void serach_delete_word_generation(){
    for (int i=0; i<6; i++) {
        int no_of_words = words_lf[i].size();
        int n = (int)(no_of_words*0.1); //10% of words lf wise

        for (int j = 0; j<n; j++) {
            int idx1 = rand() % no_of_words;
            int idx2 = rand() % no_of_words;
            words_del[i].push_back(words_lf[i][idx1]);
            words_srh[i].push_back(words_lf[i][idx2]);
    }
    }
}
void word_gen_after_del(){
    for (int i=0; i<6; i++) {
        int p = words_del[i].size();

        for (int j = 0; j<(p/2); j++) {
            int idx = rand() % p;
            words_delsrh[i].push_back(words_del[i][idx]);
        }
        for (int j = 0; j<(p/2); j++) {
            int idx = rand() % words_lf[i].size();
            words_delsrh[i].push_back(words_lf[i][idx]);
        }
    }
}
void separate_chaining_report_generation(int n, int i, double y, bool extraTab = false){
    Hash h(n);

    for (int j=0; j<words_lf[i].size(); j++) {
        h.Insert(words_lf[i][j].first,words_lf[i][j].second);
    }
    words_del.resize(10);
    words_srh.resize(10);
    serach_delete_word_generation();

    std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now();

    for (int j=0; j<words_srh[i].size(); j++) {
        bool temp = h.search(words_srh[i][j].first);
    }
    std::chrono::time_point<std::chrono::system_clock> t2 = std::chrono::system_clock::now();

    auto span1 = duration_cast<chrono::nanoseconds>(t2 - t1);
    double avg_time_before_del = span1.count() / words_srh[i].size();

    for (int j=0; j<words_del[i].size(); j++) {
        h.Delete(words_del[i][j].first);
    }
    words_delsrh.resize(10);
    word_gen_after_del();
    std::chrono::time_point<std::chrono::system_clock> t3 = std::chrono::system_clock::now();

    for (int j=0; j<words_delsrh[i].size(); j++) {
        bool temp1 = h.search(words_delsrh[i][j].first);
    }

    std::chrono::time_point<std::chrono::system_clock> t4 = std::chrono::system_clock::now();
    auto span2 = duration_cast<chrono::nanoseconds>(t4 - t3);
    double avg_time_after_del = span2.count() / words_delsrh[i].size();

    if (!extraTab) cout << fixed << y << "\t\t" << avg_time_before_del << "\t\t" << avg_time_after_del << endl;
    else cout << fixed << y << "\t\t" << avg_time_before_del << "\t\t\t\t" << avg_time_after_del << endl;
}

void linear_probing_report_generation(int n, int i, double y){
    HashLP h(n);

    for (int j=0; j<words_lf[i].size(); j++) {
        h.insertLP(words_lf[i][j].first,words_lf[i][j].second);
    }
    words_del.resize(10);
    words_srh.resize(10);
    serach_delete_word_generation();

    std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now();
    int temp = 0;
    for (int j=0; j<words_srh[i].size(); j++){
        temp += h.get(words_srh[i][j].first);
    }
    std::chrono::time_point<std::chrono::system_clock> t2 = std::chrono::system_clock::now();
    double avg_no_of_probes_befdel = temp/words_srh[i].size();

    auto span1 = duration_cast<chrono::nanoseconds>(t2 - t1);
    double avg_time_before_del = span1.count() / words_srh[i].size();

    for (int j=0; j<words_del[i].size(); j++) {
        h.delete_node(words_del[i][j].first);
    }
    words_delsrh.resize(10);
    word_gen_after_del();
    std::chrono::time_point<std::chrono::system_clock> t3 = std::chrono::system_clock::now();
    int temp1 = 0;
    for (int j=0; j<words_delsrh[i].size(); j++) {
            temp1 += h.get(words_delsrh[i][j].first);
    }
    std::chrono::time_point<std::chrono::system_clock> t4 = std::chrono::system_clock::now();
    double avg_no_of_probes_afdel = temp1/words_delsrh[i].size();
    auto span2 = duration_cast<chrono::nanoseconds>(t4 - t3);
    double avg_time_after_del = span2.count() / words_delsrh[i].size();

    cout<<fixed<<y<<"\t\t"<<avg_time_before_del<<"\t"<<avg_no_of_probes_befdel<< "\t\t"<<avg_time_after_del<<"\t"<<avg_no_of_probes_afdel<<endl;
}
void quadratic_probing_report_generation(int n, int i, double y){
    HashQP h(n);

    for (int j=0; j<words_lf[i].size(); j++) {
        h.insertQP(words_lf[i][j].first,words_lf[i][j].second);
    }
    words_del.resize(10);
    words_srh.resize(10);
    serach_delete_word_generation();

    std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now();
    int temp = 0;
    for (int j=0; j<words_srh[i].size(); j++){
        temp += h.get(words_srh[i][j].first);
    }
    std::chrono::time_point<std::chrono::system_clock> t2 = std::chrono::system_clock::now();
    double avg_no_of_probes_befdel = temp/words_srh[i].size();

    auto span1 = duration_cast<chrono::nanoseconds>(t2 - t1);
    double avg_time_before_del = span1.count() / words_srh[i].size();

    for (int j=0; j<words_del[i].size(); j++) {
        h.delete_node(words_del[i][j].first);
    }
    words_delsrh.resize(10);
    word_gen_after_del();
    std::chrono::time_point<std::chrono::system_clock> t3 = std::chrono::system_clock::now();
    int temp1 = 0;
    for (int j=0; j<words_delsrh[i].size(); j++) {
            temp1 += h.get(words_delsrh[i][j].first);
    }
    std::chrono::time_point<std::chrono::system_clock> t4 = std::chrono::system_clock::now();
    double avg_no_of_probes_afdel = temp1/words_delsrh[i].size();
    auto span2 = duration_cast<chrono::nanoseconds>(t4 - t3);
    double avg_time_after_del = span2.count() / words_delsrh[i].size();

    cout<<fixed<<y<<"\t\t"<<avg_time_before_del<<"\t"<<avg_no_of_probes_befdel<< "\t\t"<<avg_time_after_del<<"\t"<<avg_no_of_probes_afdel<<endl;
}
void double_hashing_report_generation(int n, int i, double y){
    HashDH h(n);

    for (int j=0; j<words_lf[i].size(); j++) {
        h.insertDH(words_lf[i][j].first,words_lf[i][j].second);
    }
    words_del.resize(10);
    words_srh.resize(10);
    serach_delete_word_generation();

    std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now();
    int temp = 0;
    for (int j=0; j<words_srh[i].size(); j++){
        temp += h.get(words_srh[i][j].first);
    }
    std::chrono::time_point<std::chrono::system_clock> t2 = std::chrono::system_clock::now();
    double avg_no_of_probes_befdel = temp/words_srh[i].size();

    auto span1 = duration_cast<chrono::nanoseconds>(t2 - t1);
    double avg_time_before_del = span1.count() / words_srh[i].size();

    for (int j=0; j<words_del[i].size(); j++) {
        h.delete_node(words_del[i][j].first);
    }
    words_delsrh.resize(10);
    word_gen_after_del();
    std::chrono::time_point<std::chrono::system_clock> t3 = std::chrono::system_clock::now();
    int temp1 = 0;
    for (int j=0; j<words_delsrh[i].size(); j++) {
            temp1 += h.get(words_delsrh[i][j].first);
    }
    std::chrono::time_point<std::chrono::system_clock> t4 = std::chrono::system_clock::now();
    double avg_no_of_probes_afdel = temp1/words_delsrh[i].size();
    auto span2 = duration_cast<chrono::nanoseconds>(t4 - t3);
    double avg_time_after_del = span2.count() / words_delsrh[i].size();

    cout<<fixed<<y<<"\t\t"<<avg_time_before_del<<"\t"<<avg_no_of_probes_befdel<< "\t\t"<<avg_time_after_del<<"\t"<<avg_no_of_probes_afdel<<endl;
}

void Clear(){
    for(int i = 0; i<words_del.size(); i++){
        words_del[i].clear();
    }
    for(int i = 0; i<words_srh.size(); i++){
        words_srh[i].clear();
    }
    for(int i = 0; i<words_delsrh.size(); i++){
        words_delsrh[i].clear();
    }
}

int main(){
    int sz;
    cin >> sz;


    unique_word_generation(sz);
    words_lf.resize(10);
    final_word_generation();

    double y = 0.4;

    cout << "\nTable 1: Performance of separate chaining in various load factors" << endl;
    cout << "\t\t\tBefore Deletion\tAfter Deletion" << endl;
    cout << "Load Factor" << "\t\t" << "Avg search time\t\tAvg search time" << endl;

    for (int i=0; i<6; i++) {
        separate_chaining_report_generation(sz, i, y);
        Clear();
        y += 0.1;
    }

    cout << "\nTable 2: Performance of linear probing in various load factors" << endl;
    cout << "\t\t\tBefore Deletion\t\t\t\tAfter Deletion" << endl;
    cout << "Load Factor" << "\t\t" << "Avg seach time\tAvg # of probes\t\tAvg search time\tAvg # of probes" << endl;

    y = 0.4;
    for (int i=0; i<6; i++) {
        linear_probing_report_generation(sz, i, y);
        Clear();
        y += 0.1;
    }

    cout << "\nTable 3: Performance of quadratic probing in various load factors" << endl;
    cout << "\t\t\tBefore Deletion\t\t\t\tAfter Deletion" << endl;
    cout << "Load Factor" << "\t\t" << "Avg seach time\tAvg # of probes\t\tAvg search time\tAvg # of probes" << endl;

    y = 0.4;
    for (int i=0; i<6; i++) {
        quadratic_probing_report_generation(sz, i, y);
        Clear();
        y += 0.1;
    }

    cout << "\nTable 4: Performance of double hashing in various load factors" << endl;
    y = 0.4;
    for (int i=0; i<6; i++) {
        double_hashing_report_generation(sz, i, y);
        Clear();
        y += 0.1;
    }

    cout << "\nTable 5: Performance of various collision resolution methods" << endl;

    cout << "\t\t\tBefore Deletion\t\t\t\tAfter Deletion" << endl;
    cout << "Method" << "\t\t\t" << "Avg seach time\tAvg # of probes\t\tAvg search time\tAvg # of probes" << endl;

    double LF = 0.4;
    for (int i=0; i<6; i++) {
        separate_chaining_report_generation(sz, i, LF, true);
        linear_probing_report_generation(sz, i, LF);
        quadratic_probing_report_generation(sz, i, LF);
        double_hashing_report_generation(sz, i, LF);
        cout << "Loading Factor : " << LF << endl;
        LF += 0.1;
        cout << endl;
    }

    return 0;
}
