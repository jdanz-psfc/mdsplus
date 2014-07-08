#define MPB__DECODER_K_CONG_NODES 72
#define MPB__DECODER_N_HEAD 0
#define MPB__DECODER_N_NAME 1
#define MPB__DECODER_N_COMMENT 2
#define MPB__DECODER_N_CLOCK_OUT 3
#define MPB__DECODER_N_CHANNEL_0 4
#define MPB__DECODER_N_CHANNEL_0_MODE 5
#define MPB__DECODER_N_CHANNEL_0_P1 6
#define MPB__DECODER_N_CHANNEL_0_P2 7
#define MPB__DECODER_N_CHANNEL_0_P3 8
#define MPB__DECODER_N_CHANNEL_0_P4 9
#define MPB__DECODER_N_CHANNEL_0_P5 10
#define MPB__DECODER_N_CHANNEL_0_P6 11
#define MPB__DECODER_N_CHANNEL_0_START_LOW 12
#define MPB__DECODER_N_CHANNEL_0_EDGES 13
#define MPB__DECODER_N_CHANNEL_0_EDGES_R 14
#define MPB__DECODER_N_CHANNEL_0_EDGES_F 15
#define MPB__DECODER_N_CHANNEL_0_COMMENT 16
#define MPB__DECODER_N_CHANNEL_1 17
#define MPB__DECODER_N_CHANNEL_1_MODE 18
#define MPB__DECODER_N_CHANNEL_1_P1 19
#define MPB__DECODER_N_CHANNEL_1_P2 20
#define MPB__DECODER_N_CHANNEL_1_P3 21
#define MPB__DECODER_N_CHANNEL_1_P4 22
#define MPB__DECODER_N_CHANNEL_1_P5 23
#define MPB__DECODER_N_CHANNEL_1_P6 24
#define MPB__DECODER_N_CHANNEL_1_START_LOW 25
#define MPB__DECODER_N_CHANNEL_1_EDGES 26
#define MPB__DECODER_N_CHANNEL_1_EDGES_R 27
#define MPB__DECODER_N_CHANNEL_1_EDGES_F 28
#define MPB__DECODER_N_CHANNEL_1_COMMENT 29
#define MPB__DECODER_N_CHANNEL_2 30
#define MPB__DECODER_N_CHANNEL_2_MODE 31
#define MPB__DECODER_N_CHANNEL_2_P1 32
#define MPB__DECODER_N_CHANNEL_2_P2 33
#define MPB__DECODER_N_CHANNEL_2_P3 34
#define MPB__DECODER_N_CHANNEL_2_P4 35
#define MPB__DECODER_N_CHANNEL_2_P5 36
#define MPB__DECODER_N_CHANNEL_2_P6 37
#define MPB__DECODER_N_CHANNEL_2_START_LOW 38
#define MPB__DECODER_N_CHANNEL_2_EDGES 39
#define MPB__DECODER_N_CHANNEL_2_EDGES_R 40
#define MPB__DECODER_N_CHANNEL_2_EDGES_F 41
#define MPB__DECODER_N_CHANNEL_2_COMMENT 42
#define MPB__DECODER_N_CHANNEL_3 43
#define MPB__DECODER_N_CHANNEL_3_MODE 44
#define MPB__DECODER_N_CHANNEL_3_P1 45
#define MPB__DECODER_N_CHANNEL_3_P2 46
#define MPB__DECODER_N_CHANNEL_3_P3 47
#define MPB__DECODER_N_CHANNEL_3_P4 48
#define MPB__DECODER_N_CHANNEL_3_P5 49
#define MPB__DECODER_N_CHANNEL_3_P6 50
#define MPB__DECODER_N_CHANNEL_3_START_LOW 51
#define MPB__DECODER_N_CHANNEL_3_EDGES 52
#define MPB__DECODER_N_CHANNEL_3_EDGES_R 53
#define MPB__DECODER_N_CHANNEL_3_EDGES_F 54
#define MPB__DECODER_N_CHANNEL_3_COMMENT 55
#define MPB__DECODER_N_CHANNEL_4 56
#define MPB__DECODER_N_CHANNEL_4_MODE 57
#define MPB__DECODER_N_CHANNEL_4_P1 58
#define MPB__DECODER_N_CHANNEL_4_P2 59
#define MPB__DECODER_N_CHANNEL_4_P3 60
#define MPB__DECODER_N_CHANNEL_4_P4 61
#define MPB__DECODER_N_CHANNEL_4_P5 62
#define MPB__DECODER_N_CHANNEL_4_P6 63
#define MPB__DECODER_N_CHANNEL_4_START_LOW 64
#define MPB__DECODER_N_CHANNEL_4_EDGES 65
#define MPB__DECODER_N_CHANNEL_4_EDGES_R 66
#define MPB__DECODER_N_CHANNEL_4_EDGES_F 67
#define MPB__DECODER_N_CHANNEL_4_COMMENT 68
#define MPB__DECODER_N_START_TIME 69
#define MPB__DECODER_N_START_EVENT 70
#define MPB__DECODER_N_INIT_ACTION 71
typedef struct {
	struct descriptor_xd *__xds;
	int __num_xds;
	int head_nid;
	char *name;
} InInitStruct;
