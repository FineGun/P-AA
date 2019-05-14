#include <iostream>
using namespace std;
struct Point{
    unsigned i;
    unsigned j;
};

class Foursquare{
private:
    unsigned num;
    unsigned** arr;
    unsigned** framing_arr;

public:
    void framing_odd(){
        this->set_main_sq();
        unsigned min = (num*num - 2*( (num/2) * (num/2)) - ( ((num+1)/2) * ((num+1)/2 )))+3;
        this->b_track(3, min);
        cout << min << endl;
        print_coordinates();
    }

    void framing_even(){
        for(unsigned i=0; i<num/2; i++){
            for(unsigned j=0; j<num/2; j++)
                framing_arr[i][j] = num/2;
        }

        for(unsigned i=num/2; i<num; i++){
            for(unsigned j=0; j<num/2; j++)
                framing_arr[i][j] = num/2;
        }

        for(unsigned i=0; i<num/2; i++){
            for(unsigned j=num/2; j<num; j++)
                framing_arr[i][j] = num/2;
        }

        for(unsigned i=num/2; i<num; i++){
            for(unsigned j=num/2; j<num; j++)
                framing_arr[i][j] = num/2;
        }

        cout << 4 << endl;
        print_coordinates();
    }

    void framing3(unsigned k){
        for(unsigned i=0; i<(k/3)*2; i++){
            for(unsigned j=0; j<(k/3)*2; j++)
                framing_arr[i][j] = (k/3)*2;
        }
        for(unsigned i=(k/3)*2; i<k; i++){
            for(unsigned j=0; j<k; j++)
                framing_arr[i][j] = k/3;
        }
        for(unsigned i=0; i<(k/3)*2; i++){
            for(unsigned j=(k/3)*2; j<k; j++)
                framing_arr[i][j] = k/3;
        }
        cout << 6 << endl;
        print_coordinates();
    }

    void framing5(unsigned k){
        unsigned one = (k/5)*2;
        unsigned two = (k/5)*3;
        for(unsigned i=0; i<one; i++){
            for(unsigned j=0; j<one; j++)
                framing_arr[i][j] = one;
        }

        for(unsigned i=0; i<two; i++){
            for(unsigned j=one; j<k; j++)
                framing_arr[i][j] = two;
        }

        for(unsigned i=two; i<k; i++){
            for(unsigned j=one/2; j<k; j++)
                framing_arr[i][j] = one;
        }

        for(unsigned i=one; i<two; i++){
            for(unsigned j=0; j<one; j++)
                framing_arr[i][j] = one/2;
        }

        for(unsigned i=two; i<k; i++){
            for(unsigned j=0; j< (k-(one*2)); j++)
                framing_arr[i][j] = one/2;
        }

        cout << 8 << endl;
        print_coordinates();
    }

    void b_track(unsigned count, unsigned& min){
        if(min <= count)
            return;

        Point tmp = this->find_NoClrLeft();
        if(tmp.i == num && tmp.j == num){
            if(min > count){
                min = count;
                for(unsigned j=0; j<num; j++){
                    for(unsigned k=0; k<num; k++)
                        framing_arr[j][k] = arr[j][k];
                }
            }

            return;
        }

        for(unsigned i=num/2; i>0; i--){
            if(is_fit(tmp, i)){
                count++;
                for(unsigned j=tmp.i; j<tmp.i+i; j++){
                    for(unsigned k=tmp.j; k<tmp.j+i; k++)
                        arr[j][k] = i;
                }

                b_track(count, min);
                count--;
                for(unsigned j=tmp.i; j<tmp.i+i; j++){
                    for(unsigned k=tmp.j; k<tmp.j+i; k++)
                        arr[j][k] = 0;
                }
            }
        }
    }

    bool is_fit(Point p, unsigned sz){
        for(unsigned i=p.i; i<p.i+sz; i++){
            for(unsigned j=p.j; j<p.j+sz; j++){
                if(i==num || j==num || arr[i][j])
                    return false;
            }
        }

        return true;
    }

    void set_main_sq(){
        for(unsigned i=0; i<(num+1)/2; i++){
            for(unsigned j=0; j<(num+1)/2; j++)
                arr[i][j] = (num+1)/2;
        }

        for(unsigned i=num-1; i>num/2; i--){
            for(unsigned j=0; j<num/2; j++)
                arr[i][j] = num/2;
        }

        for(unsigned i=0; i<num/2; i++){
            for(unsigned j=num-1; j>num/2; --j)
                arr[i][j] = num/2;
        }
    }

    void print_coordinates(unsigned k=1, Point cur_pos={0,0}){
        for(unsigned i=0; i<num; i++){
            for(unsigned j=0; j<num; j++){
                if(framing_arr[i][j]){
                    cout << i*k << ' ' << j*k << ' ' << k*framing_arr[i][j] << endl;
                    delete_fr_sq({i, j}, framing_arr[i][j]);
                }
            }
        }
    }

    void delete_fr_sq(Point st, unsigned sz){
        for(unsigned j=st.i; j<st.i+sz; j++){
            for(unsigned k=st.j; k<st.j+sz; k++)
                framing_arr[j][k] = 0;
        }
    }

public:
    Foursquare(unsigned sz){
        num = sz;
        arr = new unsigned*[num];
        for(unsigned i=0; i<num; i++){
            arr[i] = new unsigned[num];
            for(unsigned j=0; j<num; j++)
                arr[i][j] = 0;
        }
        framing_arr = new unsigned*[num];
        for(unsigned i=0; i<num; i++){
            framing_arr[i] = new unsigned[num];
            for(unsigned j=0; j<num; j++)
                framing_arr[i][j] = 0;
        }
    }

    void framing(){
        if(!(num%2))
            framing_even();
        else if(!(num%3))
            framing3(num);
        else if(!(num%5))
            framing5(num);
        else
            framing_odd();
    }

    Point find_NoClrLeft(){
        for(unsigned i=num/2; i<num; i++){
            for(unsigned j=num/2; j<num; j++)
            {
                if(!arr[i][j])
                    return {i, j};
            }
        }

        return {num, num};
    }

    ~Foursquare(){
        num = 0;
        for(unsigned i=0; i<num; i++){
            delete arr[i];
            delete framing_arr[i];
        }
    }
};


int main(){

    unsigned N;
    cin >> N;
    Foursquare a(N);
    a.framing();
    return 0;
}
