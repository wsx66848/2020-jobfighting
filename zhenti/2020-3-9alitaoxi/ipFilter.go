import (
	"sync"
	"time"
)

var (
	ipCount = make(map[string]int)
)

type limiter struct {
	count       int
	limitTicker int
	stop        chan int
	mutex       sync.Mutex
}

func (l *limiter) startTimer() {
	l.mutex = sync.Mutex{}
	for {
		select {
		case <-time.After(time.Minute * limitTicker):
			l.mutex.lock()
			l.count = 0
			l.mutex.unlock()
		case <-stop:
			return
		}
	}
}

func (l *limiter) addCount() {
	l.mutex.lock()
	l.count += 1
	l.mutex.Unlock()
}

func (l *limiter) banIP() {

}

func (l *limiter) stop() {
	l.stop <- 1
}

func ipFilter(ip string) {
	if _, ok := ipCount[ip]; !ok {
		ipCount[ip] = &limiter{0, 30, 30, make(chan int)}
	}

}