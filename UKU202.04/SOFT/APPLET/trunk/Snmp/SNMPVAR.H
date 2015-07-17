/* Abfragbare Variablen in der interfaces/at/ip/icmp/tcp/udp/transmission grp*/
/* alle cntr etc stehen in einem Array */
#define IF1_Spe  0
#define IF1_IOct 1
#define IF1_IUC  2
#define IF1_IBC  3
#define IF1_IDi  4
#define IF1_IErr 5
#define IF1_IUnP 6
#define IF1_OOct 7
#define IF1_OUC  8
#define IF1_OBC  9
#define IF1_ODi 10
#define UDP_IN  11
#define UDP_INP 12
#define UDP_OUT 13
#define IP_IN   14
#define IP_Rou  15
#define IP_Upr  16
#define IP_Del  17
#define IP_Out  18
#define IC_DU   19
#define IC_SQ   20
#define IC_RE   21
#define IC_ER   22
#define IC_TE   23
#define IC_PP   24
#define IC_TR   25
#define IC_OE   26
#define IC_IN   27
#define IC_IE   28
#define IC_ONP  29
#define S_varanz 30

#if 0
                  atTable OBJECT-TYPE
                          SYNTAX  SEQUENCE OF AtEntry
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { at 1 }

                  atEntry OBJECT-TYPE
                          SYNTAX  AtEntry
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { atTable 1 }

                  AtEntry ::= SEQUENCE {
                      atIfIndex
                          INTEGER,
                      atPhysAddress
                          OCTET STRING,
                      atNetAddress
                          NetworkAddress
                  }

                  atIfIndex OBJECT-TYPE
                          SYNTAX  INTEGER
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { atEntry 1 }

                  atPhysAddress OBJECT-TYPE
                          SYNTAX  OCTET STRING
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { atEntry 2 }

                  atNetAddress OBJECT-TYPE
                          SYNTAX  NetworkAddress
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { atEntry 3 }

                  -- the IP group

                  ipForwarding OBJECT-TYPE
                          SYNTAX  INTEGER {
                        gateway(1), -- entity forwards datagrams
                        host(2)     -- entity does NOT forward datagrams
                                  }
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 1 }

                  ipDefaultTTL OBJECT-TYPE
                          SYNTAX  INTEGER
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { ip 2 }

                  ipInReceives OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 3 }

                  ipInHdrErrors OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 4 }

                  ipInAddrErrors OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 5 }

                  ipForwDatagrams OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 6 }

                  ipInUnknownProtos OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 7 }

                  ipInDiscards OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 8 }

                  ipInDelivers OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 9 }

                  ipOutRequests OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 10 }

                  ipOutDiscards OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 11 }

                  ipOutNoRoutes OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 12 }

                  ipReasmTimeout OBJECT-TYPE
                          SYNTAX  INTEGER
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 13 }

                  ipReasmReqds OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 14 }

                  ipReasmOKs OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 15 }

                  ipReasmFails OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 16 }

                  ipFragOKs OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 17 }

                  ipFragFails OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 18 }

                  ipFragCreates OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 19 }

                  -- the IP Interface table

                  ipAddrTable OBJECT-TYPE
                          SYNTAX  SEQUENCE OF IpAddrEntry
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ip 20 }

                  ipAddrEntry OBJECT-TYPE
                          SYNTAX  IpAddrEntry
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ipAddrTable 1 }

                  IpAddrEntry ::= SEQUENCE {
                      ipAdEntAddr
                          IpAddress,
                      ipAdEntIfIndex
                          INTEGER,
                      ipAdEntNetMask
                          IpAddress,
                      ipAdEntBcastAddr
                          INTEGER
                  }

                  ipAdEntAddr OBJECT-TYPE
                          SYNTAX  IpAddress
                          ACCESS  read-only
                          STATUS  mandatory
                          ::=  { ipAddrEntry 1 }

                  ipAdEntIfIndex OBJECT-TYPE
                          SYNTAX  INTEGER
                          ACCESS  read-only
                          STATUS  mandatory
                          ::=  { ipAddrEntry 2 }

                  ipAdEntNetMask OBJECT-TYPE
                          SYNTAX  IpAddress
                          ACCESS  read-only
                          STATUS  mandatory
                          ::=  { ipAddrEntry 3 }

                  ipAdEntBcastAddr OBJECT-TYPE
                          SYNTAX  INTEGER
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ipAddrEntry 4 }

                  -- the IP Routing table

                  ipRoutingTable OBJECT-TYPE
                          SYNTAX  SEQUENCE OF IpRouteEntry
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { ip 21 }

                  ipRouteEntry OBJECT-TYPE
                          SYNTAX  IpRouteEntry
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { ipRoutingTable 1 }

                  IpRouteEntry ::= SEQUENCE {
                      ipRouteDest
                          IpAddress,
                      ipRouteIfIndex
                          INTEGER,
                      ipRouteMetric1
                          INTEGER,
                      ipRouteMetric2
                          INTEGER,
                      ipRouteMetric3
                          INTEGER,
                      ipRouteMetric4
                          INTEGER,
                      ipRouteNextHop
                          IpAddress,
                      ipRouteType
                          INTEGER,
                      ipRouteProto
                          INTEGER,
                      ipRouteAge
                          INTEGER
                  }

                  ipRouteDest OBJECT-TYPE
                          SYNTAX  IpAddress
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { ipRouteEntry 1 }

                  ipRouteIfIndex  OBJECT-TYPE
                          SYNTAX  INTEGER
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { ipRouteEntry 2 }

                  ipRouteMetric1 OBJECT-TYPE

                          SYNTAX  INTEGER
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { ipRouteEntry 3 }

                  ipRouteMetric2 OBJECT-TYPE
                          SYNTAX  INTEGER
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { ipRouteEntry 4 }

                  ipRouteMetric3 OBJECT-TYPE
                          SYNTAX  INTEGER
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { ipRouteEntry 5 }

                  ipRouteMetric4 OBJECT-TYPE
                          SYNTAX  INTEGER
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { ipRouteEntry 6 }

                  ipRouteNextHop OBJECT-TYPE
                          SYNTAX  IpAddress
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { ipRouteEntry 7 }

                  ipRouteType OBJECT-TYPE
                          SYNTAX  INTEGER {
                            other(1),      -- none of the following

                            invalid(2),    -- an invalidated route

                                           -- route to directly
                            direct(3),     -- connected (sub-)network

                                           -- route to a non-local
                            remote(4),     -- host/network/sub-network
                              }
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { ipRouteEntry 8 }

                  ipRouteProto OBJECT-TYPE
                          SYNTAX  INTEGER {
                            other(1),     -- none of the following

                                          -- non-protocol information
                                          --   e.g., manually
                            local(2),     --   configured entries

                                          -- set via a network
                            netmgmt(3),   --   management protocol

                                          -- obtained via ICMP,
                            icmp(4),      --   e.g., Redirect

                                          -- the following are
                                          -- gateway routing protocols
                            egp(5),
                            ggp(6),
                            hello(7),
                            rip(8),
                            is-is(9),
                            es-is(10),
                            ciscoIgrp(11),
                            bbnSpfIgp(12),
                            oigp(13)
                              }
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { ipRouteEntry 9 }

                  ipRouteAge OBJECT-TYPE
                          SYNTAX  INTEGER
                          ACCESS  read-write
                          STATUS  mandatory
                          ::= { ipRouteEntry 10 }

                  -- the ICMP group

                  icmpInMsgs OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 1 }

                  icmpInErrors OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 2 }

                  icmpInDestUnreachs OBJECT-TYPE
                          SYNTAX  Counter

                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 3 }

                  icmpInTimeExcds OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 4 }

                  icmpInParmProbs OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 5 }

                  icmpInSrcQuenchs OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 6 }

                  icmpInRedirects OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 7 }

                  icmpInEchos OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 8 }

                  icmpInEchoReps OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 9 }

                  icmpInTimestamps OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 10 }

                  icmpInTimestampReps OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 11 }

                  icmpInAddrMasks OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 12 }

                  icmpInAddrMaskReps OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 13 }

                  icmpOutMsgs OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 14 }

                  icmpOutErrors OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 15 }

                  icmpOutDestUnreachs OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 16 }

                  icmpOutTimeExcds OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 17 }

                  icmpOutParmProbs OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 18 }

                  icmpOutSrcQuenchs OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 19 }

                  icmpOutRedirects OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 20 }

                  icmpOutEchos OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 21 }

                  icmpOutEchoReps OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 22 }

                  icmpOutTimestamps OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 23 }

                  icmpOutTimestampReps OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 24 }

                  icmpOutAddrMasks OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 25 }

                  icmpOutAddrMaskReps OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { icmp 26 }

                  -- the TCP group

                  tcpRtoAlgorithm OBJECT-TYPE
                          SYNTAX  INTEGER {
                          other(1),    -- none of the following
                          constant(2), -- a constant rto
                          rsre(3),     -- MIL-STD-1778, Appendix B
                          vanj(4)      -- Van Jacobson's algorithm [11]
                                  }
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcp 1 }

                  tcpRtoMin OBJECT-TYPE
                          SYNTAX  INTEGER
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcp 2 }

                  tcpRtoMax OBJECT-TYPE
                          SYNTAX  INTEGER
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcp 3 }

                  tcpMaxConn OBJECT-TYPE
                          SYNTAX  INTEGER
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcp 4 }

                  tcpActiveOpens OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcp 5 }

                  tcpPassiveOpens OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcp 6 }

                  tcpAttemptFails OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcp 7 }

                  tcpEstabResets OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcp 8 }

                  tcpCurrEstab OBJECT-TYPE
                          SYNTAX  Gauge
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcp 9 }

                  tcpInSegs OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcp 10 }

                  tcpOutSegs OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcp 11 }

                  tcpRetransSegs OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcp 12 }

                  -- the TCP connections table

                  tcpConnTable OBJECT-TYPE
                          SYNTAX  SEQUENCE OF TcpConnEntry
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcp 13 }

                  tcpConnEntry OBJECT-TYPE
                          SYNTAX  TcpConnEntry
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcpConnTable 1 }

                  TcpConnEntry ::= SEQUENCE {
                      tcpConnState
                          INTEGER,
                      tcpConnLocalAddress
                          IpAddress,
                      tcpConnLocalPort
                          INTEGER (0..65535),
                      tcpConnRemAddress
                          IpAddress,
                      tcpConnRemPort
                          INTEGER (0..65535)
                  }

                  tcpConnState OBJECT-TYPE
                          SYNTAX  INTEGER {
                                      closed(1),
                                      listen(2),
                                      synSent(3),
                                      synReceived(4),
                                      established(5),
                                      finWait1(6),
                                      finWait2(7),
                                      closeWait(8),
                                      lastAck(9),
                                      closing(10),
                                      timeWait(11)
                                  }
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcpConnEntry 1 }

                  tcpConnLocalAddress OBJECT-TYPE
                          SYNTAX  IpAddress
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcpConnEntry 2 }

                  tcpConnLocalPort OBJECT-TYPE
                          SYNTAX  INTEGER (0..65535)
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcpConnEntry 3 }

                  tcpConnRemAddress OBJECT-TYPE
                          SYNTAX  IpAddress
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcpConnEntry 4 }

                  tcpConnRemPort OBJECT-TYPE
                          SYNTAX  INTEGER (0..65535)
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { tcpConnEntry 5 }

                  -- the UDP group

                  udpInDatagrams OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { udp 1 }

                  udpNoPorts OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { udp 2 }

                  udpInErrors OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { udp 3 }

                  udpOutDatagrams OBJECT-TYPE
                          SYNTAX  Counter
                          ACCESS  read-only
                          STATUS  mandatory
                          ::= { udp 4 }

#endif
