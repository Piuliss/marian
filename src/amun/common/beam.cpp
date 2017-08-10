#include <sstream>
#include "beam.h"

using namespace std;

namespace amunmt {

void Beam::Add(const HypothesisPtr &hypo)
{
  assert(lineNum_ == hypo->GetLineNum());
  coll_.push_back(hypo);
}

std::string Beam::Debug(size_t verbosity) const
{
  std::stringstream strm;

  strm << "size=" << size();

  if (verbosity) {
    for (size_t i = 0; i < size(); ++i) {
      const HypothesisPtr &hypo = coll_[i];
      strm << " " << hypo->GetWord();
    }
  }

  return strm.str();
}

//////////////////////////////////////////////////////////////////////////////////////////////
std::pair<bool, const Beam*> Beams::Get(size_t lineNum) const
{
  Coll::const_iterator iter = coll_.find(lineNum);
  if (iter == coll_.end()) {
    return std::pair<bool, const Beam*>(false, nullptr);
  }
  else {
    return std::pair<bool, const Beam*>(true, iter->second.get());
  }
}

BeamPtr Beams::Get(size_t lineNum)
{
  Coll::const_iterator iter = coll_.find(lineNum);
  if (iter == coll_.end()) {
    BeamPtr beam(new Beam(lineNum));
    coll_[lineNum] = beam;
    return beam;
  }
  else {
    return iter->second;
  }
}

void Beams::Add(size_t ind, HypothesisPtr &hypo)
{
  assert(hypo);
  size_t lineNum = hypo->GetLineNum();
  BeamPtr beam = Get(lineNum);
  assert(beam);
  beam->Add(hypo);
}


std::string Beams::Debug(size_t verbosity) const
{
  std::stringstream strm;

  strm << "size=" << size();

  if (verbosity) {
    for (const Coll::value_type &ele: coll_) {
      const Beam &beam = *ele.second;
      strm << endl << "\t" << beam.Debug(verbosity);
    }
  }

  return strm.str();
}


}

