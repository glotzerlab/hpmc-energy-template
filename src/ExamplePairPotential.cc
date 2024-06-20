// Copyright (c) 2009-2024 The Regents of the University of Michigan.
// Part of HOOMD-blue, released under the BSD 3-Clause License.

#include "ExamplePairPotential.h"

namespace hoomd
    {
namespace hpmc
    {

ExamplePairPotential::ExamplePairPotential(
    std::shared_ptr<SystemDefinition> sysdef)
    : PairPotential(sysdef), m_params(m_type_param_index.getNumElements())
    {
    }

LongReal ExamplePairPotential::energy(const LongReal r_squared,
                                                           const vec3<LongReal>& r_ij,
                                                           const unsigned int type_i,
                                                           const quat<LongReal>& q_i,
                                                           const LongReal charge_i,
                                                           const unsigned int type_j,
                                                           const quat<LongReal>& q_j,
                                                           const LongReal charge_j) const
    {
    unsigned int param_index = m_type_param_index(type_i, type_j);
    const auto& param = m_params[param_index];

    // TODO: implement the pair interaction
    LongReal energy = param.m_A * (r_squared - m_B);

    return energy;
    }

LongReal
ExamplePairPotential::computeRCutNonAdditive(unsigned int type_i,
                                                                  unsigned int type_j) const
    {
    unsigned int param_index = m_type_param_index(type_i, type_j);
    return m_params[param_index].m_r_cut;
    }

void ExamplePairPotential::setParamsPython(pybind11::tuple particle_types,
                                                                pybind11::dict params)
    {
    auto pdata = m_sysdef->getParticleData();
    auto type_i = pdata->getTypeByName(particle_types[0].cast<std::string>());
    auto type_j = pdata->getTypeByName(particle_types[1].cast<std::string>());
    unsigned int param_index_1 = m_type_param_index(type_i, type_j);
    m_params[param_index_1] = ParamType(params);
    unsigned int param_index_2 = m_type_param_index(type_j, type_i);
    m_params[param_index_2] = ParamType(params);

    notifyRCutChanged();
    }

pybind11::dict
ExamplePairPotential::getParamsPython(pybind11::tuple particle_types)
    {
    auto pdata = m_sysdef->getParticleData();
    auto type_i = pdata->getTypeByName(particle_types[0].cast<std::string>());
    auto type_j = pdata->getTypeByName(particle_types[1].cast<std::string>());
    unsigned int param_index = m_type_param_index(type_i, type_j);
    return m_params[param_index].asDict();
    }

ExamplePairPotential::ParamType::ParamType(pybind11::dict params)
    {
    m_A = params["A"].cast<LongReal>();
    m_B = params["B"].cast<LongReal>();
    m_r_cut = params["r_cut"].cast<LongReal>();

    if (params.is_none())
        {
        return;
        }
    }

pybind11::dict ExamplePairPotential::ParamType::asDict()
    {
    pybind11::dict pydict;
    pydict["A"] = m_A;
    pydict["B"] = m_B;
    pydict["r_cut"] = m_r_cut;
    return pydict;
    }


namespace detail
    {
void export_ExamplePairPotential(pybind11::module& m)
    {
    pybind11::class_<ExamplePairPotential,
                     PairPotential,
                     std::shared_ptr<ExamplePairPotential>>(
        m,
        "ExamplePairPotential")
        .def(pybind11::init<std::shared_ptr<SystemDefinition>>())
        .def("setParams", &ExamplePairPotential::setParamsPython)
        .def("getParams", &ExamplePairPotential::getParamsPython);
    }
    } // end namespace detail
    } // end namespace hpmc
    } // end namespace hoomd
