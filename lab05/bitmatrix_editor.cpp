#include <fstream>
#include <sstream>
#include <algorithm>
#include "bitmatrix.h"

void bye_bye()
{
  printf("ERROR: The original bitmatrix was modified.\n");
  exit(1);
}

void check_equal(Bitmatrix *b1, Bitmatrix *b2)
{
  int i, j;

  if (b1 == NULL || b2 == NULL) {
    if (b1 == b2) return;
    bye_bye();
  }

  if (b1->Rows() != b2->Rows()) bye_bye();
  if (b1->Cols() != b2->Cols()) bye_bye();
  for (i = 0; i < b1->Rows(); i++) for (j = 0; j < b1->Cols(); j++) {
    if (b1->Val(i, j) != b2->Val(i, j)) bye_bye;
  }
  return;
}

vector <string> StoSVec(string &s)
{
  istringstream ss;
  string t;
  vector <string> rv;

  ss.str(s);
  while (ss >> t) rv.push_back(t);
  return rv;
}

main(int argc, char **argv)
{
  Bitmatrix *bm, *bm2, *bm3, *bm4, *bm5;
  BM_Hash *ht;
  int i, r, c, w, v, p, b;
  string s;
  vector <string> sv;
  istringstream ss;
  string prompt = "";
  HTVec all;
  vector <int> ind;

  if (argc > 2) {
    cerr << "usage: matrix_editor [prompt]\n";
    exit(1);
  }
  if (argc == 2) prompt = argv[1];
  if (prompt.size() > 0) prompt += " ";
  bm = NULL;

  ht = new BM_Hash(10000);
  while (1) {

    cout << prompt;
    cout.flush();

    if (!getline(cin, s)) exit(0);
    sv = StoSVec(s);
    if (sv.size() > 0 && sv[0][0] != '#') {
      if (sv[0] == "EMPTY") {
        if (sv.size() != 3 || sscanf(sv[1].c_str(), "%d", &r) != 1 || r <= 0 ||
                              sscanf(sv[2].c_str(), "%d", &c) != 1 || c <= 0) {
          printf("Should be: EMPTY rows cols\n");
        } else {
          if (bm != NULL) delete bm;
          bm = new Bitmatrix(r, c);
        }
      } else if (sv[0] == "SET") {
        if (sv.size() != 4 || sscanf(sv[1].c_str(), "%d", &r) != 1 || r < 0 ||
                              sscanf(sv[2].c_str(), "%d", &c) != 1 || c < 0 ||
                              (sv[3] != "0" && sv[3] != "1")) {
          printf("Should be: SET r c 0|1\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else if (r >= bm->Rows()) {
          printf("r must be less than %d\n", bm->Rows());
        } else if (c >= bm->Cols()) {
          printf("c must be less than %d\n", bm->Cols());
        } else {
          bm->Set(r, c, sv[3][0]);
        }
      } else if (sv[0] == "VAL") {
        if (sv.size() != 3 || sscanf(sv[1].c_str(), "%d", &r) != 1 || r < 0 ||
                              sscanf(sv[2].c_str(), "%d", &c) != 1 || c < 0) {
          printf("Should be: VAL r c\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else if (r >= bm->Rows()) {
          printf("r must be less than %d\n", bm->Rows());
        } else if (c >= bm->Cols()) {
          printf("c must be less than %d\n", bm->Cols());
        } else {
          printf("%d\n", bm->Val(r, c));
        }
      } else if (sv[0] == "SWAP") {
        if (sv.size() != 3 || sscanf(sv[1].c_str(), "%d", &r) != 1 || r < 0 ||
                              sscanf(sv[2].c_str(), "%d", &c) != 1 || c < 0) {
          printf("Should be: SWAP r1 r2\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else if (r >= bm->Rows()) {
          printf("r must be less than %d\n", bm->Rows());
        } else if (c >= bm->Rows()) {
          printf("c must be less than %d\n", bm->Rows());
        } else {
          bm->Swap_Rows(r, c);
        }
      } else if (sv[0] == "+=") {
        if (sv.size() != 3 || sscanf(sv[1].c_str(), "%d", &r) != 1 || r < 0 ||
                              sscanf(sv[2].c_str(), "%d", &c) != 1 || c < 0) {
          printf("Should be: R1+=R2 r1 r2\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else if (r >= bm->Rows()) {
          printf("r must be less than %d\n", bm->Rows());
        } else if (c >= bm->Rows()) {
          printf("c must be less than %d\n", bm->Rows());
        } else {
          bm->R1_Plus_Equals_R2(r, c);
        }
      } else if (sv[0] == "PRINT") {
        w = -1;
        if (sv.size() == 1) {
          w = 0;
        } else if (sv.size() != 2 || sscanf(sv[1].c_str(), "%d", &w) != 1 || w < 0) {
          printf("Should be: PRINT [w]\n");
          w = -1;
        }
        if (w >= 0) {
          if (bm == NULL) {
            printf("No current matrix.\n");
          } else {
            bm->Print(w);
          }
        }
      } else if (sv[0] == "WRITE") {
        if (sv.size() != 2) {
          printf("Should be: WRITE filename\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else {
          bm->Write(sv[1]);
        }
      } else if (sv[0] == "PGM") {
        if (sv.size() != 4) {
          printf("Should be: PGM filename pixels border\n");
        } else if (sscanf(sv[2].c_str(), "%d", &p) == 0 || p <= 0) {
          printf("Should be: PGM filename pixels border -- pixels > 0\n");
        } else if (sscanf(sv[3].c_str(), "%d", &b) == 0 || b < 0) {
          printf("Should be: PGM filename pixels border -- border >= 0\n");
        } else {
          bm->PGM(sv[1], p, b);
        }
      } else if (sv[0] == "READ") {
        if (sv.size() != 2) {
          printf("Should be: WRITE filename\n");
        } else {
          if (bm == NULL) delete bm;
          bm = new Bitmatrix(sv[1]);
        }
      } else if (sv[0] == "STORE") {
        if (sv.size() != 2) {
          printf("Should be: STORE key\n");
        } else {
          bm2 = ht->Recall(sv[1]);
          if (bm2 != NULL) delete bm2;
          ht->Store(sv[1], bm->Copy());
        }
      } else if (sv[0] == "RECALL") {
        if (sv.size() != 2) {
          printf("Should be: RECALL key\n");
        } else {
          bm2 = ht->Recall(sv[1]);
          if (bm2 == NULL) {
            printf("No matrix with key %s\n", sv[1].c_str());
          } else {
            if (bm != NULL) delete bm;
            bm = bm2->Copy();
          }
        }
      } else if (sv[0] == "ALL") {
        if (sv.size() != 1) {
          printf("Should be: ALL\n");
        } else {
          all = ht->All();
          for (i = 0; i < all.size(); i++) {
            printf("%-30s %3d X %3d\n", all[i]->key.c_str(), all[i]->bm->Rows(), all[i]->bm->Cols());
          }
        }
      } else if (sv[0] == "SUM") {
        if (sv.size() != 3) {
          printf("Should be: SUM key1 key2\n");
        } else {
          bm2 = ht->Recall(sv[1]);
          bm3 = ht->Recall(sv[2]);
          if (bm2 == NULL) {
            printf("No matrix %s\n", sv[1].c_str());
          } else if (bm3 == NULL) {
            printf("No matrix %s\n", sv[2].c_str());
          } else if (bm2->Rows() != bm3->Rows()) {
            printf("Rows don't match\n");
          } else if (bm2->Cols() != bm3->Cols()) {
            printf("Cols don't match\n");
          } else {
            if (bm != NULL) delete bm;
            bm4 = bm2->Copy();
            bm5 = bm3->Copy();
            bm = Sum(bm2, bm3);
            check_equal(bm2, bm4);
            check_equal(bm3, bm5);
            delete bm4;
            delete bm5;
          }
        }
      } else if (sv[0] == "PRODUCT") {
        if (sv.size() != 3) {
          printf("Should be: PRODUCT key1 key2\n");
        } else {
          bm2 = ht->Recall(sv[1]);
          bm3 = ht->Recall(sv[2]);
          if (bm2 == NULL) {
            printf("No matrix %s\n", sv[1].c_str());
          } else if (bm3 == NULL) {
            printf("No matrix %s\n", sv[2].c_str());
          } else if (bm2->Cols() != bm3->Rows()) {
            printf("Dimensions don't match\n");
          } else {
            bm4 = bm2->Copy();
            bm5 = bm3->Copy();
            if (bm != NULL) delete bm;
            bm = Product(bm2, bm3);
            check_equal(bm2, bm4);
            check_equal(bm3, bm5);
            delete bm4;
            delete bm5;
          }
        }
      } else if (sv[0] == "SUBMATRIX") {
        if (sv.size() < 2) {
          printf("Should be: SUBMATRIX rows...\n");
        } else if (bm == NULL) {
          printf("No matrix %s\n", sv[1].c_str());
        } else {
          ind.clear();
          for (i = 1; i < sv.size(); i++) {
            if (sscanf(sv[i].c_str(), "%d", &r) != 1 || r < 0 || r >= bm->Rows()) {
              printf("Bad row %s. Should be a number between 0 and %d\n", 
                sv[i].c_str(), bm->Rows()-1);
              i = sv.size() + 10;
            } else {
              ind.push_back(r);
            }
          }
          if (i == sv.size()) {
            bm3 = bm->Copy();
            bm2 = Sub_Matrix(bm, ind);
            check_equal(bm, bm3);
            delete bm3;
            delete bm;
            bm = bm2;
          }
        }
      } else if (sv[0] == "INVERT") {
        if (sv.size() != 1) {
          printf("Should be: INVERT\n");
        } else  if (bm == NULL) {
          printf("No matrix %s\n", sv[1].c_str());
        } else if (bm->Rows() != bm->Cols()) {
          printf("Can't invert -- not a square matrix\n");
        } else {
          bm3 = bm->Copy();
          bm2 = Inverse(bm);
          check_equal(bm, bm3);
          delete bm3;
          if (bm2 == NULL) {
            printf("Matrix not invertible.\n");
          } else {
            delete bm;
            bm = bm2;
          }
        }
      } else if (sv[0] == "QUIT") {
        exit(0);
      } else { 
        printf("Unknown command %s\n", sv[0].c_str());
      }
    }
  }
}
