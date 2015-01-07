#include <mitdevices_msg.h>
#include <mds_gendevice.h>
#include "t2814_gen.h"
int t2814__add(struct descriptor *name_d_ptr, struct descriptor *dummy_d_ptr, int *nid_ptr)
{
  static DESCRIPTOR(library_d, "MIT$DEVICES");
  static DESCRIPTOR(model_d, "T2814");
  static DESCRIPTOR_CONGLOM(conglom_d, &library_d, &model_d, 0, 0);
  int usage = TreeUSAGE_DEVICE;
  int curr_nid, old_nid, head_nid, status;
  long int flags = NciM_WRITE_ONCE;
  NCI_ITM flag_itm[] = { {2, NciSET_FLAGS, 0, 0}, {0, 0, 0, 0} };
  char *name_ptr = strncpy(malloc(name_d_ptr->length + 1), name_d_ptr->pointer, name_d_ptr->length);
  flag_itm[0].pointer = (unsigned char *)&flags;
  name_ptr[name_d_ptr->length] = 0;
  status = TreeStartConglomerate(T2814_K_CONG_NODES);
  if (!(status & 1))
    return status;
  status = TreeAddNode(name_ptr, &head_nid, usage);
  if (!(status & 1))
    return status;
  *nid_ptr = head_nid;
  status = TreeSetNci(head_nid, flag_itm);
  status = TreePutRecord(head_nid, (struct descriptor *)&conglom_d, 0);
  if (!(status & 1))
    return status;
  status = TreeGetDefaultNid(&old_nid);
  if (!(status & 1))
    return status;
  status = TreeSetDefaultNid(head_nid);
  if (!(status & 1))
    return status;
 ADD_NODE(:INPUT_1, TreeUSAGE_SIGNAL)
      flags |= NciM_WRITE_ONCE;
  flags |= NciM_COMPRESS_ON_PUT;
  flags |= NciM_NO_WRITE_MODEL;
  status = TreeSetNci(curr_nid, flag_itm);
#define expr " [2048.,.00244141] "
 ADD_NODE_EXPR(: INPUT_1:CALIBRATION, TreeUSAGE_NUMERIC)
#undef expr
      flags |= NciM_NO_WRITE_SHOT;
  status = TreeSetNci(curr_nid, flag_itm);
 ADD_NODE(: INPUT_1:STARTIDX, TreeUSAGE_NUMERIC)
      flags |= NciM_NO_WRITE_SHOT;
  status = TreeSetNci(curr_nid, flag_itm);
 ADD_NODE(: INPUT_1:ENDIDX, TreeUSAGE_NUMERIC)
      flags |= NciM_NO_WRITE_SHOT;
  status = TreeSetNci(curr_nid, flag_itm);
 ADD_NODE(:INPUT_2, TreeUSAGE_SIGNAL)
      flags |= NciM_WRITE_ONCE;
  flags |= NciM_COMPRESS_ON_PUT;
  flags |= NciM_NO_WRITE_MODEL;
  status = TreeSetNci(curr_nid, flag_itm);
#define expr " [2048.,.00244141] "
 ADD_NODE_EXPR(: INPUT_2:CALIBRATION, TreeUSAGE_NUMERIC)
#undef expr
      flags |= NciM_NO_WRITE_SHOT;
  status = TreeSetNci(curr_nid, flag_itm);
 ADD_NODE(: INPUT_2:STARTIDX, TreeUSAGE_NUMERIC)
      flags |= NciM_NO_WRITE_SHOT;
  status = TreeSetNci(curr_nid, flag_itm);
 ADD_NODE(: INPUT_2:ENDIDX, TreeUSAGE_NUMERIC)
      flags |= NciM_NO_WRITE_SHOT;
  status = TreeSetNci(curr_nid, flag_itm);
 ADD_NODE(:INPUT_3, TreeUSAGE_SIGNAL)
      flags |= NciM_WRITE_ONCE;
  flags |= NciM_COMPRESS_ON_PUT;
  flags |= NciM_NO_WRITE_MODEL;
  status = TreeSetNci(curr_nid, flag_itm);
#define expr " [2048.,.00244141] "
 ADD_NODE_EXPR(: INPUT_3:CALIBRATION, TreeUSAGE_NUMERIC)
#undef expr
      flags |= NciM_NO_WRITE_SHOT;
  status = TreeSetNci(curr_nid, flag_itm);
 ADD_NODE(: INPUT_3:STARTIDX, TreeUSAGE_NUMERIC)
      flags |= NciM_NO_WRITE_SHOT;
  status = TreeSetNci(curr_nid, flag_itm);
 ADD_NODE(: INPUT_3:ENDIDX, TreeUSAGE_NUMERIC)
      flags |= NciM_NO_WRITE_SHOT;
  status = TreeSetNci(curr_nid, flag_itm);
 ADD_NODE(:INPUT_4, TreeUSAGE_SIGNAL)
      flags |= NciM_WRITE_ONCE;
  flags |= NciM_COMPRESS_ON_PUT;
  flags |= NciM_NO_WRITE_MODEL;
  status = TreeSetNci(curr_nid, flag_itm);
#define expr " [2048.,.00244141] "
 ADD_NODE_EXPR(: INPUT_4:CALIBRATION, TreeUSAGE_NUMERIC)
#undef expr
      flags |= NciM_NO_WRITE_SHOT;
  status = TreeSetNci(curr_nid, flag_itm);
 ADD_NODE(: INPUT_4:STARTIDX, TreeUSAGE_NUMERIC)
      flags |= NciM_NO_WRITE_SHOT;
  status = TreeSetNci(curr_nid, flag_itm);
 ADD_NODE(: INPUT_4:ENDIDX, TreeUSAGE_NUMERIC)
      flags |= NciM_NO_WRITE_SHOT;
  status = TreeSetNci(curr_nid, flag_itm);
  status = TreeEndConglomerate();
  if (!(status & 1))
    return status;
  return (TreeSetDefaultNid(old_nid));
}

int t2814__part_name(struct descriptor *nid_d_ptr, struct descriptor *method_d_ptr,
		     struct descriptor *out_d)
{
  int element = 0, status;
  NCI_ITM nci_list[] = { {4, NciCONGLOMERATE_ELT, 0, 0}, {0, 0, 0, 0} };
  nci_list[0].pointer = (unsigned char *)&element;
  status = TreeGetNci(*(int *)nid_d_ptr->pointer, nci_list);
  if (!(status & 1))
    return status;
  switch (element) {
  case (T2814_N_HEAD + 1):
    StrFree1Dx(out_d);
    break;
  case (T2814_N_INPUT_1 + 1):
 COPY_PART_NAME(:INPUT_1) break;
  case (T2814_N_INPUT_1_CALIBRATION + 1):
 COPY_PART_NAME(: INPUT_1:CALIBRATION) break;
  case (T2814_N_INPUT_1_STARTIDX + 1):
 COPY_PART_NAME(: INPUT_1:STARTIDX) break;
  case (T2814_N_INPUT_1_ENDIDX + 1):
 COPY_PART_NAME(: INPUT_1:ENDIDX) break;
  case (T2814_N_INPUT_2 + 1):
 COPY_PART_NAME(:INPUT_2) break;
  case (T2814_N_INPUT_2_CALIBRATION + 1):
 COPY_PART_NAME(: INPUT_2:CALIBRATION) break;
  case (T2814_N_INPUT_2_STARTIDX + 1):
 COPY_PART_NAME(: INPUT_2:STARTIDX) break;
  case (T2814_N_INPUT_2_ENDIDX + 1):
 COPY_PART_NAME(: INPUT_2:ENDIDX) break;
  case (T2814_N_INPUT_3 + 1):
 COPY_PART_NAME(:INPUT_3) break;
  case (T2814_N_INPUT_3_CALIBRATION + 1):
 COPY_PART_NAME(: INPUT_3:CALIBRATION) break;
  case (T2814_N_INPUT_3_STARTIDX + 1):
 COPY_PART_NAME(: INPUT_3:STARTIDX) break;
  case (T2814_N_INPUT_3_ENDIDX + 1):
 COPY_PART_NAME(: INPUT_3:ENDIDX) break;
  case (T2814_N_INPUT_4 + 1):
 COPY_PART_NAME(:INPUT_4) break;
  case (T2814_N_INPUT_4_CALIBRATION + 1):
 COPY_PART_NAME(: INPUT_4:CALIBRATION) break;
  case (T2814_N_INPUT_4_STARTIDX + 1):
 COPY_PART_NAME(: INPUT_4:STARTIDX) break;
  case (T2814_N_INPUT_4_ENDIDX + 1):
 COPY_PART_NAME(: INPUT_4:ENDIDX) break;
  default:
    status = TreeILLEGAL_ITEM;
  }
  return status;
}
