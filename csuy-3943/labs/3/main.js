'use strict';

// Global Variables
const CHART_WIDTH = 500;
const CHART_HEIGHT = 300;
const IMPORT_COLOR = '#ca0020';
const EXPORT_COLOR = '#0571b0';
const MARGIN = {
	left: 50,
	top: 30,
	bottom: 40,
	right: 30
};
const CHART_BODY_WIDTH = CHART_WIDTH - MARGIN.left - MARGIN.right;
const CHART_BODY_HEIGHT = CHART_HEIGHT - MARGIN.top - MARGIN.bottom;

const drawBarChart = (importData, exportData, year) => {
	//-------------------------- Create Scales --------------------------
	// Compute max values for scale Domain
	const maxImport = d3.max(importData, d => parseFloat(d[year]))
	const maxExport = d3.max(exportData, d => parseFloat(d[year]))

	// Create Scale for the x-axis - https://github.com/d3/d3-scale/blob/master/README.md#scaleBand
	const barBands = d3.scaleBand()
		.range([0, CHART_BODY_WIDTH])
		.domain(importData.map(d => d['Country Name']))
		.padding(0.2);

	// Create Scale for the y-axis
	// Note: We consider import values as negative, since money is leaving the country, for that reason we create a scale going from max exports as positive to max import as negative
	const yScale = d3.scaleLinear()
		.range([0, CHART_BODY_HEIGHT])
		.domain([maxExport, -maxImport]);

	//-------------------------- Draw Bars --------------------------

	// Add bars for imports - This bars are already done, once the scales are created correctly, they should appear on the screen
	const importBars = d3.select('#BarChart')
		.append('g')
		.attr('transform', `translate(${MARGIN.left}, ${MARGIN.top})`)
		.selectAll('rect')
		.data(importData)
		.enter()
		.append('rect');

	importBars
		.attr('width', barBands.bandwidth())
		.attr('height', d => yScale(-parseFloat(d[year])) - yScale(0))
		.attr('x', d => barBands(d['Country Name']))
		.attr('y', d => yScale(0))
		.attr('fill', IMPORT_COLOR)
		.append('title').text(d => `${d['Country Name']}(${d[year]/1e9})`);

	const exportBars = d3.select('#BarChart')
		.append('g')
		.attr('transform', `translate(${MARGIN.left}, ${MARGIN.top})`)
		.selectAll('rect')
		.data(exportData)
		.enter()
		.append('rect');

	exportBars
		.attr('width', barBands.bandwidth())
		.attr('height', d => yScale(-parseFloat(d[year])) - yScale(0))
		.attr('x', d => barBands(d['Country Name']))
		.attr('y', d => yScale(0) - (yScale(-parseFloat(d[year])) - yScale(0)))
		.attr('fill', EXPORT_COLOR)
		.append('title').text(d => `${d['Country Name']}(${d[year]/1e9})`);

	//-------------------------- Add Axes --------------------------
	//Create the x-axis
	const axis = d3.axisLeft(yScale)
		.tickFormat(v => v/1e9);

	d3.select('#BarChart')
		.append('g')
		.attr('transform', `translate(${MARGIN.left}, ${MARGIN.top})`)
		.call(axis)
		.append('text')
		.text('Billion $')
		.attr('dx', -MARGIN.left + 15)
		.attr('dy', MARGIN.top + 15)
		.attr('text-anchor', 'middle')
		.attr('fill', 'black')
		.attr('transform', `rotate(270, ${-MARGIN.left + 15},${MARGIN.top + 15})`);
};

const drawLineChart = (importData, exportData) => {
	//-------------------------- Prepare Data --------------------------

	// transform and combine the data, generating an array, where each item is an year with values for exports and imports.
	const data = Object.keys(importData)
		.filter(k => !isNaN(parseFloat(k))) //Remove keys that are not numbers (years)
		.map((k) => {
			return {
				'year': parseFloat(k),
				'imports': parseFloat(importData[k]),
				'exports': parseFloat(exportData[k])
			}
		});

	//-------------------------- Create Scales --------------------------
	// Compute values for scale Domain -------
	// extent computes both, min and max at the same time.
	const yearRange = d3.extent(data, d => d.year);

	// we want the overall maximum value, that is why we use Math.max to return the maximum value between imports and exports.
	// Note the diference between d3.max and Math.max, the former is a javascript function, not d3's, and it bahaves a bit different.
	const maxValue = d3.max(data, d => Math.max(d.imports, d.exports));

	// Create Scales -------
	const xScale = d3.scaleLinear()
		.range([0, CHART_BODY_WIDTH])
		.domain(yearRange);

	// Coordinates in SVG are top-bottom, but we want the line to go bottom-up, for that reason we invert the domain.
	const yScale = d3.scaleLinear()
		.range([0, CHART_BODY_HEIGHT])
		.domain([maxValue, 0]);

	//-------------------------- Draw Lines --------------------------
	// Create Line generators
	const importsLine = d3.line()
		.x(d => xScale(d.year))
		.y(d => yScale(d.imports));

	const exportsLine = d3.line()
		.x(d => xScale(d.year))
		.y(d => yScale(d.exports));

	// Add Lines
	const chartBody = d3.select('#LineChart')
		.append('g')
		.attr('transform', `translate(${MARGIN.left}, ${MARGIN.top})`)

	chartBody.append('path')
		.datum(data)
		.attr('fill', 'none')
		.attr('stroke', IMPORT_COLOR)
		.attr('d', importsLine);

	chartBody.append('path')
		.datum(data)
		.attr('fill', 'none')
		.attr('stroke', EXPORT_COLOR)
		.attr('d', exportsLine);

	//-------------------------- Add Axes --------------------------
	// Create Axes -------
	const yAxis = d3.axisLeft(yScale)
		.tickFormat(v => v/1e9);
	const xAxis = d3.axisBottom(xScale);

	d3.select('#LineChart')
		.append('g')
		.attr('transform', `translate(${MARGIN.left}, ${MARGIN.top})`)
		.call(yAxis)
		.append('text')
		.text('Billion $')
		.attr('dx', -MARGIN.left + 15)
		.attr('dy', MARGIN.top + 15)
		.attr('text-anchor', 'middle')
		.attr('fill', 'black')
		.attr('transform', `rotate(270, ${-MARGIN.left + 15}, ${MARGIN.top + 15})`)

	//**TODO 3.4 ** - Draw the X Axis
	d3.select('#LineChart')
		.append('g')
		.attr('transform', `translate(${MARGIN.left}, ${CHART_BODY_HEIGHT + MARGIN.top})`)
		.call(xAxis)
		.append('text')
		.text('Year')
		.attr('dx', CHART_BODY_WIDTH / 2)
		.attr('dy', MARGIN.top)
		.attr('text-anchor', 'middle')
		.attr('fill', 'black');
};


//------------------------------------------------------------------------------------------------------------
//The functions bellow are already complete and shoudn't be modified
//------------------------------------------------------------------------------------------------------------

const drawData = (data) => {
	// Call Function to draw the Bar Chart
	const year = 2016;
	drawBarChart(
		getDataForIndicator(data, 'Imports of goods and services (current US$)'),
		getDataForIndicator(data, 'Exports of goods and services (current US$)'),
		year
	);

	//Call Function to draw the Line chart for the given country
	const country = 'China';
	drawLineChart(
		getDataForIndicator(data, 'Imports of goods and services (current US$)', country)[0],
		getDataForIndicator(data, 'Exports of goods and services (current US$)', country)[0],
	)
}

const loadData = (url) => {
	return new Promise((resolve, reject) => {
		d3.csv(url, (err, data) => {
			if (err) {
				reject(err);
			} else {
				resolve(data);
			}
		});
	});
};

const getDataForIndicator = (data, indicator, country) => {
	//This function filters the data returning only data of a giving indicator
	let indicatorData = data.filter(d => d['Indicator Name'] === indicator);
	if (country) {
		indicatorData = indicatorData.filter(d => d['Country Name'] === country)
	}
	return indicatorData;
};

// Set the width and height of the charts SVG
d3.selectAll('#BarChart, #LineChart').attr('width', CHART_WIDTH)
d3.selectAll('#BarChart, #LineChart').attr('height', CHART_HEIGHT)

// Load the data
loadData('data.csv').then((data) => {
	drawData(data);
});
