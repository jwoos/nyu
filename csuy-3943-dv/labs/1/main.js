const descriptions = {
	html: 'HTML (Hyper Text Markup Language) is a markup language which is the way to add content to a site, considered the skeleton of the website.',
	css: 'CSS (Cascading Style Sheets) is a styling language which makes the website look good, considered the skin and out layer of the website.',
	javascript: 'JavaScript is a scripting language which adds function to the website and can be consered the muscle of the website.',
	svg: 'SVG (Scalable Vector Graphics) is a type of image that makes use of vectors which are mathematically defined and thus never lose quality no matter how much it is zoomed in or out.'
};

for (let k of Object.keys(descriptions)) {
	const elem = document.querySelector(`li#item-${k}`);
	elem.addEventListener('click', () => {
		document.querySelector('#description').innerText = descriptions[k];
	});
}
