#include <pcap/pcap.h>
#include <stdio.h>

#define DEVICE ("en0")

int main(int argc, char *argv[]) {
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_if_t *alldevs;

  if (pcap_findalldevs(&alldevs, errbuf)) {
    fprintf(stderr, "fnd default dev..");
    return 2;
  }

  for (pcap_if_t *d = alldevs; d != NULL; d = d->next) {
    printf("Device name: %s\n", d->name);
  }

  pcap_t *handle;
  handle = pcap_open_live(DEVICE, BUFSIZ, 0, 1000, errbuf);
  printf("open handle. \n");

  bpf_u_int32 mask;
  bpf_u_int32 net;
  if (pcap_lookupnet(DEVICE, &net, &mask, errbuf)) {
    fprintf(stderr, "error when lookup net");
    return 3;
  }

  struct bpf_program bp;
  if (pcap_compile(handle, &bp, "port 80", 0, net)) {
    fprintf(stderr, "error when compile pcap filter");
    return 3;
  }

  if (pcap_setfilter(handle, &bp)) {
    fprintf(stderr, "error when set filter");
    return 4;
  }

  struct pcap_pkthdr header;
  const u_char *packet;
  packet = pcap_next(handle, &header);
  /* print its length */
  printf("jacked a packet with length of [%d]\n", header.len);
  /* and close the session */
  printf("packet: %s\n", packet);
  pcap_close(handle);

  return 0;
}
