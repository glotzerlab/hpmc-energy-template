// Copyright (c) 2009-2024 The Regents of the University of Michigan.
// Part of HOOMD-blue, released under the BSD 3-Clause License.

#include "ExampleExternalPotential.h"

namespace hoomd
    {
namespace hpmc
    {

ExampleExternalPotential::ExampleExternalPotential(
    std::shared_ptr<SystemDefinition> sysdef)
    : ExternalPotential(sysdef), m_params(m_type_param_index.getNumElements())
    {
    }

LongReal ExampleExternalPotential::particleEnergyImplementation(unsigned int type_i,
                                                               const vec3<LongReal>& r_i,
                                                               const quat<LongReal>& q_i,
                                                               LongReal charge_i,
                                                               bool trial)
    {
    // TODO: implement the functional form of the external potential.
    return m_epsilon[type_i] * dot(r_i, r_i);
    }


void ExampleExternalPotential::setParamsPython(const std::string& particle_type,
                                                                pybind11::dict params)
    {
    unsigned int particle_type_id = m_sysdef->getParticleData()->getTypeByName(particle_type);
    m_params[particle_type_id] = ParamType(params);
    notifyRCutChanged();
    }

pybind11::dict
ExampleExternalPotential::getParamsPython(const std::string& particle_type)
    {
    unsigned int particle_type_id = m_sysdef->getParticleData()->getTypeByName(particle_type);
    return m_params[particle_type_id].asDict();
    }

ExampleExternalPotential::ParamType::ParamType(pybind11::dict params)
    {
    if (params.is_none())
        {
        return;
        }

    pybind11::dict v = params;

    // TODO: unpack per-type quanties declared in header file
    m_epsilon = v["epsilon"].cast<LongReal>();
    }

pybind11::dict ExampleExternalPotential::ParamType::asDict()
    {
    pybind11::dict pydict;
    // TODO; pack per-type quantities declared in header file
    pydict["epsilon"] = m_epsilon;
    return pydict;
    }


namespace detail
    {
void export_PairPotentialShortRangeSurfaceInteraction(pybind11::module& m)
    {
    pybind11::class_<ExampleExternalPotential,
                     PairPotential,
                     std::shared_ptr<ExampleExternalPotential>>(
        m,
        "ExampleExternalPotential")
        .def(pybind11::init<std::shared_ptr<SystemDefinition>>())
        .def("setParams", &ExampleExternalPotential::setParamsPython)
        .def("getParams", &ExampleExternalPotential::getParamsPython);
    }
    } // end namespace detail
    } // end namespace hpmc
    } // end namespace hoomd