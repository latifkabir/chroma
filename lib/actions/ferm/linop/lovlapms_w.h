// -*- C++ -*-
// $Id: lovlapms_w.h,v 1.4 2003-10-20 20:31:50 edwards Exp $
/*! \file
 *  \brief Internal Overlap-pole operator
 */

#ifndef __lovlapms_w_h__
#define __lovlapms_w_h__

#include "linearop.h"

using namespace QDP;

//! Internal Overlap-pole operator
/*!
 * \ingroup linop
 *
 * This routine is specific to Wilson fermions!
 *
 *   Chi  =   (1/2)*((1+m_q) + (1-m_q) * gamma_5 * B) . Psi 
 *  where  B  is the pole approx. to eps(H(m)) 
 *
 * Internally, it computes
 *   Chi  =   ((1+m_q)/(1-m_q) + gamma_5 * B) . Psi 
 * and then rescales at the end to the correct normalization
 *
 *  NOTE: B is hermitian, so       
 *     (1 + gamma_5 * B)^dag = (1 + B * gamma_5) 
 *                           = gamma_5 * (1 + gamma_5 * B) * gamma_5 
 */

class lovlapms : public LinearOperator<LatticeFermion>
{
public:
  //! Creation routine
  /*!
   * \ingroup linop
   *
   * \param _MdagM          M^dag.M of underlying linop M      (Read)
   * \param _M              Underlying linop M	               (Read)
   * \param _m_q            quark mass                         (Read)
   * \param _numroot 	    number of poles in expansion       (Read)
   * \param _constP         constant coeff                     (Read)
   * \param _resP           numerator                          (Read)
   * \param _rootQ          denom                              (Read)
   * \param _OperEigVec     eigenvectors      	               (Read)
   * \param _EigValFunc     eigenvalues      	               (Read)
   * \param _NEig           number of eigenvalues              (Read)
   * \param _RsdCG          residual for inner CG              (Read)
   */
  lovlapms(const LinearOperator<LatticeFermion>& _MdagM, const LinearOperator<LatticeFermion>& _M, 
	   const Real& _m_q, int _numroot, const Real& _constP, 
	   const multi1d<Real>& _resP,
	   const multi1d<Real>& _rootQ, 
	   const multi1d<LatticeFermion>& _EigVec,
	   const multi1d<Real>& _EigValFunc,
	   int _NEig, const Real& _RsdCG) :
    MdagM(_MdagM), M(_M), m_q(_m_q), numroot(_numroot), constP(_constP),
    resP(_resP), rootQ(_rootQ), OperEigVec(_OperEigVec), EigValFunc(_EigValFunc),
    NEig(_NEig), RsdCG(_RsdCG) {}

  //! Destructor is automatic
  ~lovlapms() {}

  //! Only defined on the entire lattice
  const OrderedSubset& subset() const {return all;}

  //! Apply the operator onto a source vector
  LatticeFermion operator() (const LatticeFermion& psi, enum LinOpSign isign) const;

private:
  const LinearOperator<LatticeFermion>& MdagM;
  const LinearOperator<LatticeFermion>& M;
  const Real& m_q;
  int numroot;
  const Real& constP;
  const multi1d<Real>& rootQ;
  const multi1d<Real>& resP;
  const multi1d<LatticeFermion>& EigVec;
  const multi1d<Real>& EigValFunc;
  int NEig;
  const Real& RsdCG;

};

#endif
