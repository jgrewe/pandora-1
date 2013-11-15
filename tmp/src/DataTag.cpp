// Copyright (c) 2013, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#include <pandora/DataSet.hpp>
#include <pandora/DataTag.hpp>
#include <pandora/Util.hpp>

using namespace std;

namespace pandora {


DataTag::DataTag(const DataTag &tag)
    : EntityWithSources(tag.file, tag.block, tag.group, tag.entity_id),reference_list(tag.reference_list)
{
    representation_group = tag.representation_group;
}


DataTag::DataTag(File file, const Block block, Group group, const std::string &id)
    : EntityWithSources(file, block, group, id), reference_list(group, "references")
{
    representation_group = group.openGroup("representations");
}


DataTag::DataTag(File file, const Block block, Group group, const std::string &id, time_t time)
    : EntityWithSources(file, block, group, id, time),reference_list(group, "references")
{
    representation_group = group.openGroup("representations");
}


DataArray DataTag::positions() const {
    std::string posId;
    group.getAttr("positions", posId);
    if(posId.length() > 0){
        if(this->block.hasDataArray(posId))
            return this->block.getDataArray(posId);
    }
    throw runtime_error("Unable to find DataArray with id " + posId + "!");
}


void DataTag::positions(const DataArray &positions) {
    this->positions(positions.id());
}


void DataTag::positions(const string &positionsId) {
    if(!this->block.hasDataArray(positionsId)){
        throw runtime_error("DataTag::extents: cannot set Extent because referenced DataArray does not exist!");
    }
    else{
        if(this->hasExtents()){
            DataArray pos = this->block.getDataArray(positionsId);
            DataArray ext = this->extents();
            if(!checkDimensions(ext,pos))
                throw runtime_error("DataTag::positions: cannot set Positions because dimensionality of extent and position data do not match!");
        }
        group.setAttr("positions", positionsId);
        forceUpdatedAt();
    }
}

bool DataTag::hasPositions() const{
    std::string posId;
    group.getAttr("positions", posId);
    return (posId.length() > 0);
}

DataArray DataTag::extents() const {
    std::string extId;
    group.getAttr("extents", extId);
    if(extId.length() > 0){
        if(this->block.hasDataArray(extId))
            return this->block.getDataArray(extId);
    }
    throw runtime_error("Unable to find DataArray with id " + extId + "!");
}


void DataTag::extents(const DataArray &extent) {
    extents(extent.id());
}


void DataTag::extents(const string &extentsId) {
    if(!this->block.hasDataArray(extentsId)){
        throw runtime_error("DataTag::extents: cannot set Extent because referenced DataArray does not exist!");
    }
    else{
        if(this->hasPositions()){
            DataArray ext = this->block.getDataArray(extentsId);
            DataArray pos = this->positions();
            if(!checkDimensions(ext,pos))
                throw runtime_error("DataTag::extents: cannot set Extent because dimensionality of extent and position data do not match!");
        }
        group.setAttr("extents", extentsId);
        forceUpdatedAt();
    }
}


bool DataTag::hasExtents() const{
    std::string extId;
    group.getAttr("extents", extId);
    return (extId.length() > 0);
}

// Methods concerning references.

bool DataTag::hasReference(const DataArray &reference) const {
    return hasReference(reference.id());
}


bool DataTag::hasReference(const std::string &id) const {
    return reference_list.has(id);
}


size_t DataTag::referenceCount() const {
    return reference_list.count();
}


DataArray DataTag::getReference(const std::string &id) const {
    if (hasReference(id)) {
        return block.getDataArray(id);
    } else {
        throw runtime_error("No reference with id: " + id);
    }
}


void DataTag::addReference(const DataArray &reference) {
    reference_list.add(reference);
}


bool DataTag::removeReference(const DataArray &reference) {
    return reference_list.remove(reference);
}


std::vector<DataArray> DataTag::references() const {
    vector<string> refs = reference_list.get();
    vector<DataArray> data_obj;

    for (size_t i = 0; i < refs.size(); i++) {
        if (block.hasDataArray(refs[i])) {
            data_obj.push_back(block.getDataArray(refs[i]));
        } else {
            // TODO ???
        }
    }
    return data_obj;
}


void DataTag::references(const std::vector<DataArray> &references) {
    vector<string> ids(references.size());

    for (size_t i = 0; i < references.size(); i++) {
        ids[i] = references[i].id();
    }

    reference_list.set(ids);
}

// Methods concerning representations.

bool DataTag::hasRepresentation(const string &id) const{
    return representation_group.hasGroup(id);
}


size_t DataTag::representationCount() const{
    return representation_group.objectCount();
}


Representation DataTag::getRepresentation(const std::string &id) const{
    return Representation(representation_group.openGroup(id, false), id, this->block);
}


Representation DataTag::getRepresentation(size_t index) const{
    string id = representation_group.objectName(index);
    Representation r(representation_group.openGroup(id), id, this->block);
    return r;
}


std::vector<Representation> DataTag::representations() const{
    vector<Representation>  representation_obj;
    size_t count = representation_group.objectCount();
    for (size_t i = 0; i < count; i++) {
        string id = representation_group.objectName(i);
        Representation r(representation_group.openGroup(id, false), id, this->block);
        representation_obj.push_back(r);
    }
    return representation_obj;
}


Representation DataTag::createRepresentation(DataArray data, LinkType link_type){
    string id = util::createId("representation");
    while(representation_group.hasObject(id))
        id = util::createId("representation");
    Representation r(representation_group.openGroup(id, true), id, this->block);
    r.linkType(link_type);
    r.data(data);
    return r;
}


bool DataTag::removeRepresentation(const string &id){
    if (representation_group.hasGroup(id)) {
        representation_group.removeGroup(id);
        return true;
    } else {
        return false;
    }
}

// Other methods and functions

DataTag& DataTag::operator=(const DataTag &other) {
    if (*this != other) {
        this->file = other.file;
        this->block = other.block;
        this->group = other.group;
        this->entity_id = other.entity_id;
        this->representation_group = other.representation_group;
        this->sources_refs = other.sources_refs;
        this->reference_list = other.reference_list;
    }
    return *this;
}


ostream& operator<<(ostream &out, const DataTag &ent) {
    out << "DataTag: {name = " << ent.name();
    out << ", type = " << ent.type();
    out << ", id = " << ent.id() << "}";
    return out;
}


bool DataTag::checkDimensions(const DataArray &a, const DataArray &b)const{
    bool valid = true;
    boost::multi_array<double,1> aData, bData;
    a.getRawData(aData);
    b.getRawData(bData);
    valid = aData.num_dimensions() == bData.num_dimensions();
    if(!valid)
        return valid;

    boost::multi_array<double,1>::size_type dims = aData.num_dimensions();
    for(boost::multi_array<double,1>::size_type i = 0; i < *aData.shape(); i++){
        valid = (aData.shape()[i] != bData.shape()[i]);
        if(!valid)
            return valid;
    }
    return valid;
}


bool DataTag::checkPositionsAndExtents() const{
    bool valid = true;
    if(hasPositions() && hasExtents()){
        DataArray pos = positions();
        DataArray ext = extents();
        boost::multi_array<double,1> posData, extData;
        pos.getRawData(posData);
        ext.getRawData(extData);
        return checkDimensions(pos, ext);
    }
    return valid;
}


DataTag::~DataTag() {}


} /* namespace pandora */