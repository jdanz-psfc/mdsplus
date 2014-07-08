#include <mitdevices_msg.h>
#include <mds_gendevice.h>
#include "l2415_gen.h"
int l2415__add(struct descriptor *name_d_ptr, struct descriptor *dummy_d_ptr, int *nid_ptr)
{
	static DESCRIPTOR(library_d, "MIT$DEVICES");
	static DESCRIPTOR(model_d, "L2415");
	static DESCRIPTOR_CONGLOM(conglom_d, &library_d, &model_d, 0, 0);
	int usage = TreeUSAGE_DEVICE;
	int curr_nid, old_nid, head_nid, status;
	long int flags = NciM_WRITE_ONCE;
	NCI_ITM flag_itm[] = {{2, NciSET_FLAGS, 0, 0},{0, 0, 0, 0}};
	char *name_ptr = strncpy(malloc(name_d_ptr->length+1),name_d_ptr->pointer,name_d_ptr->length);
	flag_itm[0].pointer = (unsigned char *)&flags;
	name_ptr[name_d_ptr->length]=0;
	status = TreeStartConglomerate(L2415_K_CONG_NODES);
	if (!(status & 1)) return status;
	status = TreeAddNode(name_ptr, &head_nid, usage);
	if (!(status & 1)) return status;
	*nid_ptr = head_nid;
	 status = TreeSetNci(head_nid, flag_itm);
	status = TreePutRecord(head_nid, (struct descriptor *)&conglom_d,0);
	if (!(status & 1)) return status;
	status = TreeGetDefaultNid(&old_nid);
	if (!(status & 1)) return status;
	status = TreeSetDefaultNid(head_nid);
	if (!(status & 1)) return status;
	ADD_NODE(:NAME, TreeUSAGE_TEXT)
	ADD_NODE(:COMMENT, TreeUSAGE_TEXT)
#define expr " 1.	"
	ADD_NODE_EXPR(:POLARITY, TreeUSAGE_NUMERIC)
#undef expr
	flags |= NciM_NO_WRITE_SHOT;
	 status = TreeSetNci(curr_nid, flag_itm);
#define expr " 3500.	"
	ADD_NODE_EXPR(:RANGE, TreeUSAGE_NUMERIC)
#undef expr
	flags |= NciM_NO_WRITE_SHOT;
	 status = TreeSetNci(curr_nid, flag_itm);
#define expr " 0.	"
	ADD_NODE_EXPR(:CURRENT, TreeUSAGE_NUMERIC)
#undef expr
	flags |= NciM_NO_WRITE_SHOT;
	 status = TreeSetNci(curr_nid, flag_itm);
#define expr " 0.	"
	ADD_NODE_EXPR(:VOLTAGE, TreeUSAGE_NUMERIC)
#undef expr
	flags |= NciM_NO_WRITE_SHOT;
	 status = TreeSetNci(curr_nid, flag_itm);
	ADD_NODE(:CURR_OUT, TreeUSAGE_NUMERIC)
	flags |= NciM_WRITE_ONCE;
	flags |= NciM_NO_WRITE_MODEL;
	 status = TreeSetNci(curr_nid, flag_itm);
	ADD_NODE(:VOLT_OUT, TreeUSAGE_NUMERIC)
	flags |= NciM_WRITE_ONCE;
	flags |= NciM_NO_WRITE_MODEL;
	 status = TreeSetNci(curr_nid, flag_itm);
	ADD_NODE_ACTION(:INIT_ACTION, INIT, INIT, 50, 0, 0, CAMAC_SERVER, 0)
	ADD_NODE_ACTION(:STORE_ACTION, STORE, STORE, 50, 0, 0, CAMAC_SERVER, 0)
	status = TreeEndConglomerate();
		if (!(status & 1)) return status;
	return(TreeSetDefaultNid(old_nid));
}

int l2415__part_name(struct descriptor *nid_d_ptr, struct descriptor *method_d_ptr, struct descriptor *out_d)
{
	int element = 0, status;
 	NCI_ITM nci_list[] = {{4, NciCONGLOMERATE_ELT, 0, 0},{0,0,0,0}};
	nci_list[0].pointer = (unsigned char *)&element;
	status = TreeGetNci(*(int *)nid_d_ptr->pointer, nci_list);
		if (!(status & 1)) return status;
	switch(element)  {
		case(L2415_N_HEAD + 1) : StrFree1Dx(out_d); break;
		case(L2415_N_NAME + 1) : COPY_PART_NAME(:NAME) break;
		case(L2415_N_COMMENT + 1) : COPY_PART_NAME(:COMMENT) break;
		case(L2415_N_POLARITY + 1) : COPY_PART_NAME(:POLARITY) break;
		case(L2415_N_RANGE + 1) : COPY_PART_NAME(:RANGE) break;
		case(L2415_N_CURRENT + 1) : COPY_PART_NAME(:CURRENT) break;
		case(L2415_N_VOLTAGE + 1) : COPY_PART_NAME(:VOLTAGE) break;
		case(L2415_N_CURR_OUT + 1) : COPY_PART_NAME(:CURR_OUT) break;
		case(L2415_N_VOLT_OUT + 1) : COPY_PART_NAME(:VOLT_OUT) break;
		case(L2415_N_INIT_ACTION + 1) : COPY_PART_NAME(:INIT_ACTION) break;
		case(L2415_N_STORE_ACTION + 1) : COPY_PART_NAME(:STORE_ACTION) break;
		default : status = TreeILLEGAL_ITEM;
	}
	return status;
}

	extern int l2415___init();
#define free_xd_array { int i; for(i=0; i<1;i++) if(work_xd[i].l_length) MdsFree1Dx(&work_xd[i],0);}
#define error(nid,code,code1) {free_xd_array return GenDeviceSignal(nid,code,code1);}

int l2415__init(struct descriptor *nid_d_ptr, struct descriptor *method_d_ptr)
{
	declare_variables(InInitStruct)
	struct descriptor_xd work_xd[1];
	int xd_count = 0;
	memset((char *)work_xd, '\0', sizeof(struct descriptor_xd) * 1);
	initialize_variables(InInitStruct)

	read_string_error(L2415_N_NAME,name, DEV$_BAD_NAME);
	read_float(L2415_N_POLARITY,polarity);
	read_float(L2415_N_RANGE,range);
	read_float(L2415_N_CURRENT,current);
	read_float(L2415_N_VOLTAGE,voltage);
	status = l2415___init(nid_d_ptr, &in_struct);
	free_xd_array
	return status;
}
#undef free_xd_array


	extern int l2415___store();
#define free_xd_array { int i; for(i=0; i<1;i++) if(work_xd[i].l_length) MdsFree1Dx(&work_xd[i],0);}

int l2415__store(struct descriptor *nid_d_ptr, struct descriptor *method_d_ptr)
{
	declare_variables(InStoreStruct)
	struct descriptor_xd work_xd[1];
	int xd_count = 0;
	memset((char *)work_xd, '\0', sizeof(struct descriptor_xd) * 1);
	initialize_variables(InStoreStruct)

	read_string_error(L2415_N_NAME,name, DEV$_BAD_NAME);
	status = l2415___store(nid_d_ptr, &in_struct);
	free_xd_array
	return status;
}
#undef free_xd_array
