/*
 * const ver = document.querySelector('#version');
 * ver.innerText = d3.version;
 */
d3.select('#version').text(`D3 Loaded - version: ${d3.version}`);

const loadCSV = (url) => {
	return new Promise((resolve, reject) => {
		d3.csv(url, (err, data) => {
			if (err) {
				reject(err);
			} else {
				resolve(data);
			}
		});
	});
}

const drawChart1 = (data) => {
	const chart = d3.select('#chart1');

	const items = chart.selectAll('g')
		.data(data)
		.enter()
		.append('g')
		.attr('transform', d => `translate(${d.x}, ${d.y})`);

	items.append('rect')
		.attr('width', d => d.width)
		.attr('height', d => d.height)
		.attr('fill', d => d.color);
};

const drawChart2 = (data) => {
	const chart = d3.select('#chart2');
	console.log(data)

	const xScale = d3.scaleLinear()
		.range([0, 200])
		.domain([0, d3.max(data, d => parseInt(d.GDP))]);

	const yScale = d3.scaleLinear()
		.range([0, 150])
		.domain([0, data.length]);

	const colorScale = d3.scaleOrdinal()
		.range(d3.schemeCategory10.slice(1))
		.domain(data.map(d => d.Country));

	const items = chart.selectAll('g')
		.data(data)
		.enter()
		.append('g')
		.attr('transform', (d, i) => `translate(0, ${yScale(i)})`);

	items.append('rect')
		.attr('width', d => xScale(d.GDP))
		.attr('height', 20)
		.attr('fill', d => colorScale(d.Country));

	items.append('text')
		.text(d => d.Country)
		.attr('text-anchor', 'start')
		.attr('alignment-baseline', 'before-edge')
		.attr('dx', d => xScale(d.GDP) + 10);
};

loadCSV('data.csv').then((data) => {
	d3.select('#records').text(`Num Records: ${data.length}`);
	drawChart1(data);
}, (err) => alert(err));

loadCSV('data2.csv').then((data) => {
	drawChart2(data);
}, (err) => alert(err));
