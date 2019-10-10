#######################################################
# 
# ResDumpCommand.py
# Python implementation of the Class ResDumpCommand
# Generated by Enterprise Architect
# Created on:      14-Aug-2019 10:11:58 AM
# Original author: talve
# 
#######################################################
from abc import ABC, abstractmethod


class ResDumpCommand(ABC):
    """This class is an interface for the resource dump commands and perform a
    strategy pattern of the execution by calling the internal methods.
      validate, get_data and print_data that will be implemented by each command.
    """
    def execute(self):
        """Command execution call:
           1. validate.
           2. get_data.
           3. print_data.
        """
        self.validate()
        self.get_data()
        self.print_data()

    @abstractmethod
    def get_data(self):
        """get the needed data.
        """
        pass

    @abstractmethod
    def print_data(self, data):
        """Print the collected data.
        """
        pass

    @abstractmethod
    def validate(self):
        """validate.
        """
        pass
