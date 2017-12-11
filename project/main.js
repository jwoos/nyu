const DIMENSION = {
	width: 1900,
	height: 950,
	margin: {
		left: 75,
		right: 25,
		top: 100,
		bottom: 75
	}
};

DIMENSION.trueWidth = DIMENSION.width - (DIMENSION.margin.left + DIMENSION.margin.right);
DIMENSION.trueHeight = DIMENSION.height - (DIMENSION.margin.top + DIMENSION.margin.bottom);

const monthQuarterMap = {
	1: 1,
	4: 2,
	7: 3,
	10: 4
};
window.monthQuarterMap = monthQuarterMap;

const CONTAINER = '#chart';

const loadData = () => {
	return new Promise((resolve, reject) => {
		d3.queue()
			.defer(d3.json, 'Las Vegas Business.json')
			.await((err, ...data) => {
				if (err) {
					reject(err);
				} else {
					resolve(data);
				}
			});
	});
};

const init = (container) => {
	d3.select(CONTAINER)
		.attr('width', DIMENSION.width)
		.attr('height', DIMENSION.height);
};

const transformData = (data) => {
	const transformed = {};

	const categories = {};
	transformed.categories = categories;

	const years = new Set();
	transformed.years = years;

	const dates = new Set();
	transformed.dates = dates;

	for (let restaurant of data) {
		const category = restaurant.category;

		for (let q of restaurant.quarters) {
			const date = new Date(`${q.quarter} EST`);

			years.add(date.getFullYear());
			dates.add(q.quarter);
			q.quarter = date;
		}

		if (!categories[category]) {
			categories[category] = [restaurant];
		} else {
			categories[category].push(restaurant);
		}

		restaurant.quarters.sort((a, b) => {
			const aQuarter = a.quarter;
			const bQuarter = b.quarter;

			if (aQuarter < bQuarter) {
				return -1;
			} else if (aQuarter > bQuarter) {
				return 1;
			} else {
				return 0;
			}
		});
	}

	transformed.years = Array.from(transformed.years).sort();
	transformed.dates = Array.from(transformed.dates).sort().map(d => new Date(`${d} EST`));

	return transformed;
};

loadData().then(([data]) => {
	init(CONTAINER);

	const transformed = transformData(data);

	window.transformed = transformed;
	window.data = data;

	const container = d3.select(CONTAINER);

	const colorScale = d3.scaleOrdinal()
		.range(d3.schemeCategory20)
		.domain(Object.keys(transformed.categories));

	const axisYearScale = d3.scaleBand();
	const axisQuarterScale = d3.scaleBand();

	const xYearScale = d3.scaleLinear()
		.range([0, DIMENSION.trueWidth])
		.domain(d3.extent(transformed.years, d => d));
	const xScale = d3.scaleTime()
		.range([0, DIMENSION.trueWidth])
		.domain([transformed.dates[0], transformed.dates[transformed.dates.length - 1]]);
	const yScale = d3.scaleLinear()
		.range([DIMENSION.trueHeight, 0])
		.domain([1, 5]);

	const linesContainer = {};
	for (let k of Object.keys(transformed.categories)) {
		linesContainer[k] = container.append('g')
			.attr('transform', `translate(${DIMENSION.margin.left}, ${DIMENSION.margin.top})`)
			.attr('class', `category-${k}`);
	}

	for (let restaurant of data) {
		const line = d3.line()
			.x(d => xScale(d.quarter))
			.y(d => yScale(d.rating));

		linesContainer[restaurant.category].append('path')
			.datum(restaurant.quarters)
			.attr('fill', 'none')
			.attr('stroke', colorScale(restaurant.category))
			.attr('d', line);
	}

	const xAxis = d3.axisLeft(yScale)
		.ticks(10);
	const yAxis = d3.axisBottom(xScale)
		.ticks(50)
		.tickFormat(v => `${v.getFullYear()} Q${monthQuarterMap[v.getMonth() + 1]}`);

	const axes = container.append('g')
		.attr('transform', `translate(${DIMENSION.margin.left}, ${DIMENSION.margin.top})`);

	// x-axis
	axes.append('g')
		.call(xAxis)
		.append('text')
		.text('Average Rating')
		.attr('dx', -30)
		.attr('dy', DIMENSION.trueHeight / 2)
		.attr('text-anchor', 'middle')
		.attr('fill', 'black')
		.attr('font-size', 14)
		.attr('transform', `rotate(270, -30, ${DIMENSION.trueHeight / 2})`);

	// y-axis
	const axesY = axes.append('g')
		.attr('transform', `translate(0, ${DIMENSION.trueHeight})`);

	axesY.call(yAxis)
		.selectAll('text')
		.attr('transform', 'rotate(-90, 0, 13)')
		.attr('text-anchor', 'end')

	axesY.append('text')
		.text('Quarter')
		.attr('dx', DIMENSION.trueWidth / 2)
		.attr('dy', 65)
		.attr('text-anchor', 'middle')
		.attr('fill', 'black')
		.attr('font-size', 14);
});
