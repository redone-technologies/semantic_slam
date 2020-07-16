#!/usr/bin/env python3
from owlready2 import *

class TOSMDatabaseSPARQL:
    def __init__(self, owl_file_name, owl_file_path):
        # Load parameters from ROS
        self.owl_file_name = owl_file_name
        self.owl_file_path = owl_file_path

        # Load an OWL file into the world and synchronize with a hermit reasoner
        self.onto = World()
        self.onto.get_ontology("file://" + self.owl_file_path + self.owl_file_name).load()
        sync_reasoner(self.onto, infer_property_values=True)
        self.graph = self.onto.as_rdflib_graph()

        print()
        print("[TOSM Database SPARQL] Ready to use the database **" + self.owl_file_name)
        print()
        print("INFORMATION")
        print("* number of classes: ", len(list(self.onto.classes())))
        print("* number of individuals: ", len(list(self.onto.individuals())))
        print("* number of object properties: ", len(list(self.onto.object_properties())))
        print("* number of data properties: ", len(list(self.onto.data_properties())))
        print()

    # output: query results
    def query_connected_places(self):
        query = []
        query.append("PREFIX tosm: <http://www.semanticweb.org/ses/tosm#> ")
        query.append("SELECT ?s ?o ")
        query.append("WHERE { ?s  tosm:isConnectedTo ?o .")
        query.append("""?s  tosm:isLeafPlace  "true" .""")
        query.append("""?o  tosm:isLeafPlace  "true" . }""")
        query = ''.join(query)
        
        # query = "PREFIX tosm: <http://www.semanticweb.org/ses/tosm#> SELECT ?o ?s WHERE { ?s  tosm:isConnectedTo ?o }"

        # query = """
        # PREFIX tosm: <http://www.semanticweb.org/ses/tosm#>
        # SELECT ?s ?o
        # WHERE {
        #         ?s  tosm:isConnectedTo  ?o .
        #         ?s  tosm:isLeafPlace  "true" .
        #         ?o  tosm:isLeafPlace  "true" .
        #       }
        # """

        resultsList = self.graph.query(query)

        return resultsList

    # output: query results
    def qeury_door_insideOf_doorway(self):
        query = []
        query.append("PREFIX tosm: <http://www.semanticweb.org/ses/tosm#> ")
        query.append("SELECT ?s ?o ")
        query.append("WHERE { ?s  tosm:isInsideOf  ?o.")
        # to find only places
        query.append(""" ?o rdf:type tosm:Doorway. }""")
        query = ''.join(query)

        resultsList = self.graph.query(query)

        return resultsList


    # input: obj_prop (string)
    #        ex) "isConnectedTo"
    # output: query results
    def query_places(self, obj_prop):
        query = []
        query.append("PREFIX tosm: <http://www.semanticweb.org/ses/tosm#> ")
        query.append("SELECT ?o ?s ")
        query.append("WHERE { ?o  tosm:")
        query.append(obj_prop)
        query.append("  ?s . ")
        # to find only places
        query.append(""" ?o  tosm:isLeafPlace  "true" . }""")
        query = ''.join(query)
        
        # query = "PREFIX tosm: <http://www.semanticweb.org/ses/tosm#> SELECT ?o ?s WHERE { ?s  tosm:isConnectedTo ?o }"

        # query = """
        # PREFIX tosm: <http://www.semanticweb.org/ses/tosm#>
        # SELECT ?o ?s
        # WHERE {
        #         ?o  tosm:isConnectedTo  ?s .
        #         ?o  tosm:isLeafPlace  "true" .
        #       }
        # """

        resultsList = self.graph.query(query)

        return resultsList


    # output: query results
    def query_leaf_places(self):
        query = []
        query.append("PREFIX tosm: <http://www.semanticweb.org/ses/tosm#> ")
        query.append("SELECT ?s ")
        query.append("""WHERE { ?s  tosm:isLeafPlace  "true" }""")
        query = ''.join(query)

        resultsList = self.graph.query(query)

        return resultsList