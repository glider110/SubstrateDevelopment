代码块：

- **main函数输入：**

```c++
 using namespace std;
int main(int argc, char **argv)
{
    cout<<"argc: "<<argc<<endl;
    for(int i=0;i<=argc;++i)
    {
        cout<<i<<"  ";
        cout<<argv[i]<<"   "<<endl;      
    }
    return 0;
}
```


```c++
cv::Mat disp8 = cv::Mat(height, width, CV_8UC1);
for (sint32 i = 0; i < height; i++)
{
for (sint32 j = 0; j < width; j++)
{
// disp8.data[i * width + j]= disparity[i * width + j];
disp8.at<uint8_t>(i,j)= disparity[i * width + j];
}
}
```
