/**
 *	\file graph.cpp
 *
 * 	This file is subject to the terms and conditions defined in
 * 	files 'BSD.txt' and 'GPL.txt'. For a list of authors see file 'AUTHORS'.
 */

#include "graph.h"

#include <boost/graph/graphviz.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/mcgregor_common_subgraphs.hpp>
#include <boost/graph/isomorphism.hpp>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <set>
#include <string>
#include <algorithm>

using namespace std;
using namespace boost;

FlowGraph::FlowGraph(string localIPLabel,
		string localIPShape,
		string protocolLabel,
		string protocolShape,
		string localPortLabel,
		string localPortShape,
		string localPort2RemotePortLabel,
		string localPort2RemotePortDirection,
		string localPort2RemotePortColor,
		string remotePortLabel,
		string remotePortShape,
		string remotePort2RemoteIPLabel,
		string remotePort2RemoteIPColor,
		string remoteIPLabel,
		string remoteIPShape) :
			localIPLabel(localIPLabel),
			localIPShape(localIPShape),
			protocolLabel(protocolLabel),
			protocolShape(protocolShape),
			localPortLabel(localPortLabel),
			localPortShape(localPortShape),
			localPort2RemotePortLabel(localPort2RemotePortLabel),
			localPort2RemotePortDirection(localPort2RemotePortDirection),
			localPort2RemotePortColor(localPort2RemotePortColor),
			remotePortLabel(remotePortLabel),
			remotePortShape(remotePortShape),
			remotePort2RemoteIPLabel(remotePort2RemoteIPLabel),
			remotePort2RemoteIPColor(remotePort2RemoteIPColor),
			remoteIPLabel(remoteIPLabel),
			remoteIPShape(remoteIPShape) {
}

bool FlowGraph::operator==(const FlowGraph &other) const {
	if (localIPLabel != other.localIPLabel)
		return false;
	if (localIPShape != other.localIPShape)
		return false;
	if (protocolLabel != other.protocolLabel)
		return false;
	if (protocolShape != other.protocolShape)
		return false;
	if (localPortLabel != other.localPortLabel)
		return false;
	if (localPortShape != other.localPortShape)
		return false;
	if (localPort2RemotePortLabel != other.localPort2RemotePortLabel)
		return false;
	if (localPort2RemotePortDirection != other.localPort2RemotePortDirection)
		return false;
	if (localPort2RemotePortColor != other.localPort2RemotePortColor)
		return false;
	if (remotePortLabel != other.remotePortLabel)
		return false;
	if (remotePortShape != other.remotePortShape)
		return false;
	if (remotePort2RemoteIPLabel != other.remotePort2RemoteIPLabel)
		return false;
	if (remotePort2RemoteIPColor != other.remotePort2RemoteIPColor)
		return false;
	if (remoteIPLabel != other.remoteIPLabel)
		return false;
	if (remoteIPShape != other.remoteIPShape)
		return false;
	return true;
}

bool FlowGraph::operator<(const FlowGraph &other) const {
	if (localIPLabel.compare(other.localIPLabel) < 0)
		return true;
	else if (localIPLabel.compare(other.localIPLabel) > 0)
		return false;

	if (localIPShape.compare(other.localIPShape) < 0)
		return true;
	else if (localIPShape.compare(other.localIPShape) > 0)
		return false;

	if (protocolLabel.compare(other.protocolLabel) < 0)
		return true;
	else if (protocolLabel.compare(other.protocolLabel) > 0)
		return false;

	if (protocolShape.compare(other.protocolShape) < 0)
		return true;
	else if (protocolShape.compare(other.protocolShape) > 0)
		return false;

	if (localPortLabel.compare(other.localPortLabel) < 0)
		return true;
	else if (localPortLabel.compare(other.localPortLabel) > 0)
		return false;

	if (localPortShape.compare(other.localPortShape) < 0)
		return true;
	else if (localPortShape.compare(other.localPortShape) > 0)
		return false;

	if (localPort2RemotePortLabel.compare(other.localPort2RemotePortLabel) < 0)
		return true;
	else if (localPort2RemotePortLabel.compare(other.localPort2RemotePortLabel) > 0)
		return false;

	if (localPort2RemotePortDirection.compare(other.localPort2RemotePortDirection) < 0)
		return true;
	else if (localPort2RemotePortDirection.compare(other.localPort2RemotePortDirection) > 0)
		return false;

	if (localPort2RemotePortColor.compare(other.localPort2RemotePortColor) < 0)
		return true;
	else if (localPort2RemotePortColor.compare(other.localPort2RemotePortColor) > 0)
		return false;

	if (remotePortLabel.compare(other.remotePortLabel) < 0)
		return true;
	else if (remotePortLabel.compare(other.remotePortLabel) > 0)
		return false;

	if (remotePortShape.compare(other.remotePortShape) < 0)
		return true;
	else if (remotePortShape.compare(other.remotePortShape) > 0)
		return false;

	if (remotePort2RemoteIPLabel.compare(other.remotePort2RemoteIPLabel) < 0)
		return true;
	else if (remotePort2RemoteIPLabel.compare(other.remotePort2RemoteIPLabel) > 0)
		return false;

	if (remotePort2RemoteIPColor.compare(other.remotePort2RemoteIPColor) < 0)
		return true;
	else if (remotePort2RemoteIPColor.compare(other.remotePort2RemoteIPColor) > 0)
		return false;

	if (remoteIPLabel.compare(other.remoteIPLabel) < 0)
		return true;
	else if (remoteIPLabel.compare(other.remoteIPLabel) > 0)
		return false;

	if (remoteIPShape.compare(other.remoteIPShape) < 0)
		return true;
	else if (remoteIPShape.compare(other.remoteIPShape) > 0)
		return false;

	return false;
}

std::ostream& FlowGraph::print(std::ostream &os) const {
	os << "localIPLabel: " << localIPLabel << "\n";
	os << "localIPShape: " << localIPShape << "\n";
	os << "protocolLabel: " << protocolLabel << "\n";
	os << "protocolShape: " << protocolShape << "\n";
	os << "localPortLabel: " << localPortLabel << "\n";
	os << "localPortShape: " << localPortShape << "\n";
	os << "localPort2RemotePortLabel: " << localPort2RemotePortLabel << "\n";
	os << "localPort2RemotePortDirection: " << localPort2RemotePortDirection << "\n";
	os << "localPort2RemotePortColor: " << localPort2RemotePortColor << "\n";
	os << "remotePortLabel: " << remotePortLabel << "\n";
	os << "remotePortShape: " << remotePortShape << "\n";
	os << "remotePort2RemoteIPLabel: " << remotePort2RemoteIPLabel << "\n";
	os << "remotePort2RemoteIPColor: " << remotePort2RemoteIPColor << "\n";
	os << "remoteIPLabel: " << remoteIPLabel << "\n";
	os << "remoteIPShape: " << remoteIPShape << endl;
	return os;
}

/**
 * Represents a graphviz dot graph
 *
 * \exception std::exception
 */
DotGraph::DotGraph(std::ifstream &dotInputStream) {
	prepareGraphProperties();
	try {
		importDotGraph(dotInputStream);
	} catch (std::exception &e) {
		throw e;
	}
}

/**
 * Reads a graphviz dot graph from an ifstream
 *
 * \param dotInputStream std::ifstream that contains the graphviz dot graph to import
 *
 * \exception std::string Errormessage
 */
void DotGraph::importDotGraph(std::ifstream &dotInputStream) {
	// this is needed, since some (all?) version of boost print out the whole graph to std::cerr in read_graphviz()
	std::streambuf * cerr_save = std::cerr.rdbuf();
	std::stringstream sinkStreambuf;
	std::cerr.rdbuf(sinkStreambuf.rdbuf());
	try {
		read_graphviz(dotInputStream, graph, dp);
		// restore std::cerr
		std::cerr.rdbuf(cerr_save);
	} catch (std::exception &e) {
		std::cerr.rdbuf(cerr_save);
		std::string errormessage("Error while importing graphviz dot graph. ");
		errormessage += e.what();
		throw errormessage;
	} catch (...) {
		std::cerr.rdbuf(cerr_save);
		exit(1); // this *should* never happen
	}
}

/**
 * Set up the properties used in the graphviz dot graphs
 */
void DotGraph::prepareGraphProperties() {
	// set up all the properties for the edges and nodes. Stored as member variable
	// to save us from calling boost::get_property for almost all of them

	//vertices
	vertices_name = boost::get(vertex_name, graph);
	dp.property("node_id", vertices_name);

	vertices_url = boost::get(vertex_url_t(), graph);
	dp.property("URL", vertices_url);

	vertices_fontsize = boost::get(vertex_fontsize_t(), graph);
	dp.property("fontsize", vertices_fontsize);

	vertices_label = boost::get(vertex_label_t(), graph);
	dp.property("label", vertices_label);

	vertices_draw = boost::get(vertex_draw_t(), graph);
	dp.property("_draw_", vertices_draw);

	vertices_shape = boost::get(vertex_shape_t(), graph);
	dp.property("shape", vertices_shape);

	vertices_ldraw = boost::get(vertex_ldraw_t(), graph);
	dp.property("_ldraw_", vertices_ldraw);

	vertices_height = boost::get(vertex_height_t(), graph);
	dp.property("height", vertices_height);

	vertices_width = boost::get(vertex_width_t(), graph);
	dp.property("width", vertices_width);

	vertices_pos = boost::get(vertex_pos_t(), graph);
	dp.property("pos", vertices_pos);

	vertices_style = boost::get(vertex_style_t(), graph);
	dp.property("style", vertices_style);

	vertices_rolnum = boost::get(vertex_rolnum_t(), graph);
	dp.property("rolnum", vertices_rolnum);

	vertices_ip = boost::get(vertex_ip_t(), graph);
	dp.property("ip", vertices_ip);

	vertex_fontname = boost::get(vertex_fontname_t(), graph);
	dp.property("fontname", vertex_fontname);

	//edges
	edges_color = boost::get(edge_color_t(), graph);
	dp.property("color", edges_color);

	edges_dir = get(edge_dir_t(), graph);
	dp.property("dir", edges_dir);

	edges_label = boost::get(edge_label_t(), graph);
	dp.property("label", edges_label);

	edges_style = boost::get(edge_style_t(), graph);
	dp.property("style", edges_style);

	edges_draw = boost::get(edge_draw_t(), graph);
	dp.property("_draw_", edges_draw);

	edges_pos = boost::get(edge_pos_t(), graph);
	dp.property("pos", edges_pos);

	edges_hdraw = boost::get(edge_hdraw_t(), graph);
	dp.property("_hdraw_", edges_hdraw);

	edges_ldraw = boost::get(edge_ldraw_t(), graph);
	dp.property("_ldraw_", edges_ldraw);

	edges_tdraw = boost::get(edge_tdraw_t(), graph);
	dp.property("_tdraw_", edges_tdraw);

	edges_lp = boost::get(edge_lp_t(), graph);
	dp.property("lp", edges_lp);

	//graph
	graph_name = boost::get_property(graph, graph_name_t());
	dp.property("name", boost::ref_property_map<BoostGraph*, std::string>(boost::get_property(graph, boost::graph_name)));

	graph_rankdir = boost::get_property(graph, graph_rankdir_t());
	dp.property("rankdir", boost::ref_property_map<BoostGraph*, std::string>(boost::get_property(graph, graph_rankdir_t())));

	graph_draw = boost::get_property(graph, graph_draw_t());
	dp.property("_draw_", boost::ref_property_map<BoostGraph*, std::string>(boost::get_property(graph, graph_draw_t())));

	graph_bb = boost::get_property(graph, graph_bb_t());
	dp.property("bb", boost::ref_property_map<BoostGraph*, std::string>(boost::get_property(graph, graph_bb_t())));

	graph_xdotversion = boost::get_property(graph, graph_xdotversion_t());
	dp.property("xdotversion", boost::ref_property_map<BoostGraph*, std::string>(boost::get_property(graph, graph_xdotversion_t())));

	graph_shape = boost::get_property(graph, graph_shape_t());
	dp.property("shape", boost::ref_property_map<BoostGraph*, std::string>(boost::get_property(graph, graph_shape_t())));

	graph_style = boost::get_property(graph, graph_style_t());
	dp.property("style", boost::ref_property_map<BoostGraph*, std::string>(boost::get_property(graph, graph_style_t())));
}

/**
 * Compare two graphviz dot graph. // TODO: have to elaborate more what we do in here
 *
 * \param other Graph to compare to
 *
 * \return bool True if both graphs are equal
 */
bool DotGraph::equal(DotGraph &other, FlowContainer &thisFlows, FlowContainer &otherFlows) {
	FlowGraph temporaryFlowGraph;
	GraphVertexIterator this_lIP = findLocalIP(*this);
	GraphVertexIterator other_lIP = findLocalIP(other);

	this->buildFlowset(*this_lIP, temporaryFlowGraph, 1, thisFlows);
	other.buildFlowset(*other_lIP, temporaryFlowGraph, 1, otherFlows);

	for (FlowContainer::iterator thisit = thisFlows.begin(); thisit != thisFlows.end();) { // TODO: would std::set_difference do the job as well?
		FlowContainer::iterator otherit = otherFlows.find(*thisit);
		if (otherit != otherFlows.end()) {
			otherFlows.erase(otherit);
			thisFlows.erase(thisit++);
		} else {
			thisit++;
		}
	}

	return thisFlows.empty() && otherFlows.empty();
}

bool DotGraph::equalVerbose(DotGraph &other) {
	if (!isomorphism(other)) {
		cout << "Graphs are not isomorph!" << endl;
		return false;
	}

	FlowContainer thisUnmatched, otherUnmatched;
	bool isEqual = equal(other, thisUnmatched, otherUnmatched);
	if(isEqual) {
		return true;
	} else {
		cout << "Graphs are not equal." << endl;
		cout << "Unmatched flows on first graph: " << endl;
		for(FlowContainer::iterator it = thisUnmatched.begin(); it != thisUnmatched.end(); it++) {
			it->print(cout);
			cout << endl;
		}
		cout << "Unmatched flows on second graph: " << endl;
		for(FlowContainer::iterator it = thisUnmatched.begin(); it != thisUnmatched.end(); it++) {
			it->print(cout);
			cout << endl;
		}
	}
	return false;
}

void DotGraph::buildFlowset(Vertex v, FlowGraph &prototype, unsigned int k_level, FlowContainer &results) {
	BoostGraph::out_edge_iterator a, b;
	boost::tie(a, b) = out_edges(v, graph);
	property_map<BoostGraph, vertex_name_t>::type this_name_map = get(vertex_name, graph);
	stringstream prefixss;
	prefixss << "k" << (k_level + 1) << "_";
	string prefix_following = prefixss.str();

	switch (k_level) {
		case 1:
			prototype.localIPLabel = get(vertices_label, v);
			prototype.localIPShape = get(vertices_shape, v);
			break;
		case 2:
			prototype.protocolLabel = get(vertices_label, v);
			prototype.protocolShape = get(vertices_shape, v);
		case 3:
			prototype.localPortLabel = get(vertices_label, v);
			prototype.localPortShape = get(vertices_shape, v);
			break;
		case 4:
			prototype.remotePortLabel = get(vertices_label, v);
			prototype.remotePortShape = get(vertices_shape, v);
			break;
		case 5:
			prototype.remoteIPLabel = get(vertices_label, v);
			prototype.remoteIPShape = get(vertices_shape, v);
			results.insert(prototype);
			return;
	}

	for (BoostGraph::out_edge_iterator it = a; it != b; it++) {
		Vertex v1 = target(*it, graph);
		Vertex v2 = source(*it, graph);
		Vertex v;

		string name1 = get(this_name_map, v1);
		string name2 = get(this_name_map, v2);

		if (name1.find(prefix_following) != string::npos) {
			v = v1;
		} else if (name2.find(prefix_following) != string::npos) {
			v = v2;
		} else {
			continue;
		}

		switch (k_level) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				prototype.localPort2RemotePortColor = get(edges_color, *it);
				prototype.localPort2RemotePortDirection = get(edges_dir, *it);
				prototype.localPort2RemotePortLabel = get(edges_label, *it);
				break;
			case 4:
				prototype.remotePort2RemoteIPColor = get(edges_color, *it);
				prototype.remotePort2RemoteIPLabel = get(edges_label, *it);
				break;
		}
		buildFlowset(v, prototype, k_level + 1, results);
	}
}
/**
 * Check two graphviz dot graphs for their isomorphism
 *
 * \param other Graph to test for isomorphism
 *
 * \return bool True if the graphs are isomorph
 */
bool DotGraph::isomorphism(DotGraph &other) {
	GraphVertexIterator this_vertex_iterator_begin, this_vertex_iterator_end, other_vertex_iterator_begin, other_vertex_iterator_end;
	GraphEdgeIterator this_edge_iterator_begin, this_edge_iterator_end, other_edge_iterator_begin, other_edge_iterator_end;

	boost::tie(this_vertex_iterator_begin, this_vertex_iterator_end) = vertices(graph);
	boost::tie(other_vertex_iterator_begin, other_vertex_iterator_end) = vertices(other.graph);

	int this_n = std::distance(this_vertex_iterator_begin, this_vertex_iterator_end);
	int other_n = std::distance(other_vertex_iterator_begin, other_vertex_iterator_end);

	std::vector<graph_traits<BoostGraph>::vertex_descriptor> f(this_n > other_n ? this_n : other_n);

	property_map<BoostGraph, vertex_index_t>::type v1_index_map = get(vertex_index, this->graph), v2_index_map = get(vertex_index, other.graph);

	bool returnvalue = boost::isomorphism(this->graph, other.graph, isomorphism_map(make_iterator_property_map(f.begin(), v1_index_map, f[0])));
	return returnvalue;
}

DotGraph::GraphVertexIterator DotGraph::findLocalIP(DotGraph &graph) {
	GraphVertexIterator vertexIteratorBegin, vertexIteratorEnd;
	boost::tie(vertexIteratorBegin, vertexIteratorEnd) = vertices(graph.graph);
	GraphVertexIterator vertexIterator = vertexIteratorBegin;
	GraphVertexIterator localIPVertex;

	int localIPcounter = 0;
	while (vertexIterator != vertexIteratorEnd) {
		if (graph.vertices_name[*vertexIterator].find("k1_") == 0) {
			localIPcounter++;
			localIPVertex = vertexIterator;
		}
		vertexIterator++;
	}
	assert(localIPcounter == 1);
	return localIPVertex;
}
