# Some general notes about the project

### Rain gauge

Current rain gauge is a tipper style that uses 0.2794mm (0.11 in) per click. For reference, here are some very hastily searched values of rainfall around the world:

    -Average annual rainfall (mm/year):
        - Mawsynram, India (allegedly the "wettest place in the world"): 12,000
        - New York City: 1,300
        - Mobile, AL: 1,600
        - Seattle, WA: 1,000
        - London, UK: 600
        - New Delhi, India: 800
        - Tokyo, Japan: 1,500
        - Death Valley, CA: 60
    - Some estimated min/max values:
        - wettest possible year: 26,000mm/year
        - driest possible year: 0mm/year
        - world record rainfall rate: 300mm/hour
        - upper rainfall rates in a hurricane: 55mm/hour

This translates to some very rough estimates for number of rows created each year:

    - Absolute max:
        - 100,000 rows per year
    - Realistic max:
        - 50,000 rows per year
    - Average flow in most US cities:
        - less than 5,000 rows per year
    - Expected flow in arid climates:
        - 2,000 rows or less per year

For flow rate, the gauge can handle a max flow rate of ????? mm/hour.
