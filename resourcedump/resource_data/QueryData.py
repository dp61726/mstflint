#######################################################
# 
# QueryData.py
# Python implementation of the Class QueryData
# Generated by Enterprise Architect
# Created on:      14-Aug-2019 10:12:02 AM
# Original author: talve
# 
#######################################################
from fetchers.ResourceDumpFetcher import ResourceDumpFetcher
from filters.SegmentsFilter import SegmentsFilter
from utils import constants


class QueryData:
    """this class is responsible for getting the menu segment.
    """

    @classmethod
    def get_query(cls, device_name, vhca_id):
        """this method is getting the query segments by using the CoreDumpFetcher and
        filter it by removing the none menu segments.
        """
        try:
            query_kwargs = {'segment': constants.RESOURCE_DUMP_SEGMENT_TYPE_MENU,
                            'vHCAid': vhca_id, 'index1': 0, 'index2': 0, 'numOfObj1': 0, 'numOfObj2': 0, 'depth': 0}
            query_segments = ResourceDumpFetcher(device_name).fetch_data(**query_kwargs)
            res = SegmentsFilter.get_segments(query_segments, constants.RESOURCE_DUMP_SEGMENT_TYPE_MENU)
            try:
                menu = res[0]
            except Exception as _:
                raise Exception("Menu segment wasn't found after filtering by menu type")
            return menu
        except Exception as e:
            raise Exception("Failed to fetch query data with exception: {0}".format(e))
