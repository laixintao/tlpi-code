package main

import (
	"context"
	"fmt"
	"time"

	clientv3 "github.com/coreos/etcd/clientv3"
)

func main() {
	cli, err := clientv3.New(clientv3.Config{
		Endpoints:   []string{"localhost:2379"},
		DialTimeout: 5 * time.Second,
	})
	if err != nil {
		// handle error!
	}
	defer cli.Close()
	ctx := context.Background()
	fmt.Printf("start to watch prefix /...")
	rch := cli.Watch(ctx, "/", clientv3.WithPrefix(), clientv3.WithProgressNotify())

	for wresp := range rch {
		for _, ev := range wresp.Events {
			fmt.Printf("%s %q : %q\n", ev.Type, ev.Kv.Key, ev.Kv.Value)
		}
	}
}
