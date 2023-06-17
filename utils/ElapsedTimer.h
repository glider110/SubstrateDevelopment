/************************************************************************************
**
** MIT License
** 
** Copyright (c) 2020 Wu Shaoguang
** 
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** 
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
** 
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
************************************************************************************/
 
#ifndef ELAPSED_TIMER_H_
#define ELAPSED_TIMER_H_
 
#include <chrono>
 
/** \class ElapsedTimer
    \brief Defines an elapsed timer.
*/
template<class TimeT = double>
class ElapsedTimer
{
public:
    using chrono_clock_type = std::chrono::high_resolution_clock;
    using time_point = typename chrono_clock_type::time_point;
    using time_t = TimeT;
    
    /** Constructs a elapsed timer, and start timing. */
    ElapsedTimer() : m_tp(chrono_clock_type::now()) {}
 
    /** Restart timing. */
    void reset()
    {
        m_tp = chrono_clock_type::now();
    }
    
    /** Returns the elapsed time in milliseconds. */
    time_t elapsed() const
    {
        return elapsedMilliseconds();
    }
    
    /** Returns the elapsed time in nanoseconds. */
    time_t elapsedNanoseconds() const
    {
        return std::chrono::duration_cast<nanoseconds_t>(chrono_clock_type::now() - m_tp).count();
    }
    
    /** Returns the elapsed time in microseconds. */
    time_t elapsedMicroseconds() const
    {
        return std::chrono::duration_cast<microseconds_t>(chrono_clock_type::now() - m_tp).count();
    }
    
    /** Returns the elapsed time in milliseconds. */
    time_t elapsedMilliseconds() const
    {
        return std::chrono::duration_cast<milliseconds_t>(chrono_clock_type::now() - m_tp).count();
    }
    
    /** Returns the elapsed time in seconds. */
    time_t elapsedSeconds() const
    {
        return std::chrono::duration_cast<seconds_t>(chrono_clock_type::now() - m_tp).count();
    }
    
    /** Returns the elapsed time in minutes.  */
    time_t elapsedMinutes() const
    {
        return std::chrono::duration_cast<minutes_t>(chrono_clock_type::now() - m_tp).count();
    }
    
    /** Returns the elapsed time in hours. */
    time_t elapsedHours() const
    {
        return std::chrono::duration_cast<hours_t>(chrono_clock_type::now() - m_tp).count();
    }
 
private:
    using nanoseconds_t = std::chrono::duration<time_t, std::chrono::nanoseconds::period>;
    using microseconds_t = std::chrono::duration<time_t, std::chrono::microseconds::period>;
    using milliseconds_t = std::chrono::duration<time_t, std::chrono::milliseconds::period>;
    using seconds_t = std::chrono::duration<time_t, std::chrono::seconds::period>;
    using minutes_t = std::chrono::duration<time_t, std::chrono::minutes::period>;
    using hours_t = std::chrono::duration<time_t, std::chrono::hours::period>;
 
    time_point m_tp;
};
 
#endif // ELAPSED_TIMER_H_