#include "CSG.h"

bool UnionRule(bool l_hit, bool in_l, bool in_r) {
  return (l_hit && !in_r) || (!l_hit && !in_l);
}

bool IntersectRule(bool l_hit, bool in_l, bool in_r) {
  return (l_hit && in_r) || (!l_hit && in_l);
}

bool DifferenceRule(bool l_hit, bool in_l, bool in_r) {
  return (l_hit && !in_r) || (!l_hit && in_l);
}